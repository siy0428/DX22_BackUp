#include "mydirectx.h"
#include <d3dx9.h>
#include "texture.h"
#include "input.h"

//====================================================
//�\���̐錾
//====================================================
typedef struct Mesh_Vertex_tag
{
	D3DXVECTOR3 position;	//���W
	D3DXVECTOR3 normal;		//�@���x�N�g��
	D3DCOLOR color;			//�F���
	D3DXVECTOR2 UV;			//�e�N�X�`��
}MeshVertex;
#define FVF_MESH (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)

//====================================================
//�O���[�o���ϐ�
//====================================================
static MeshVertex g_mesh_vertex;
static LPDIRECT3DVERTEXBUFFER9 lpVtxBuf;   // ���_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 lpIdxBuf;    // ���_�C���f�b�N�X�o�b�t�@
static unsigned int g_tex = NULL;
static int g_width;
static int g_height;
static int g_vertex_num;
static int g_index_num;

//=====================================================
//������
//=====================================================
void MeshField_Init(int width, int height, int texId)
{
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_width = width;	//��
	g_height = height;	//����
	g_vertex_num = (width + 1) * (height + 1);	//���_��
	g_index_num = g_vertex_num + (height - 1) * (width + 1) + (height - 1) * 2;	//�C���f�b�N�X��
	g_tex = texId;

	pDevice->CreateVertexBuffer(sizeof(MeshVertex) * g_vertex_num, 0, (D3DFORMAT)FVF_MESH, D3DPOOL_MANAGED, &lpVtxBuf, NULL);

	// ���b�N
	MeshVertex *vbuf;
	lpVtxBuf->Lock(0, 0, (void**)(&vbuf), D3DLOCK_NOSYSLOCK);

	//���_�f�[�^������
	for (int i = 0; i < g_vertex_num; i++)
	{
		vbuf[i].position = D3DXVECTOR3((FLOAT)(i % (g_width + 1) - g_width / 2), 0.0f, (FLOAT)(-i / (g_width + 1)) + g_height / 2);
		vbuf[i].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vbuf[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		vbuf[i].UV = D3DXVECTOR2((FLOAT)(i % (g_width + 1)) - g_width / 2, (FLOAT)(-i / (g_width + 1)) + g_height / 2);
	}

	// ���
	lpVtxBuf->Unlock();

	pDevice->CreateIndexBuffer(g_index_num * sizeof(MeshVertex), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &lpIdxBuf, NULL);

	// �m�ۂ��钸�_�C���f�b�N�X�o�b�t�@��錾
	unsigned short*    ibuf;
	// ���b�N
	lpIdxBuf->Lock(0, 0, (void**)(&ibuf), D3DLOCK_NOSYSLOCK);

	// ���_�C���f�b�N�X�̊m��
	unsigned short index_num = 0;	//�k�ރ|���S���̐ݒ肪�s��ꂽ��
	for (unsigned short i = 0; i < g_index_num / 2; i++)
	{
		//�k�ރ|���S��
		if ((g_width + 1) + (g_width + 2) * index_num == i && i != 0 && i != g_index_num / 2 && g_height > 1)
		{
			ibuf[i + i] = i - 1 - index_num;
			ibuf[i + i + 1] = (g_width + 1) + (i - index_num);
			index_num++;
		}
		//�ʏ�C���f�b�N�X
		else
		{
			ibuf[i + i] = (g_width + 1) + (i - index_num);
			ibuf[i + i + 1] = (i - index_num);
		}
	}

	// ���
	lpIdxBuf->Unlock();
}

//=====================================================
//�I��
//=====================================================
void MeshField_Uninit(void)
{
	if (lpVtxBuf)
	{
		lpVtxBuf->Release();
		lpVtxBuf = NULL;
	}
	if (lpIdxBuf)
	{
		lpIdxBuf->Release();
		lpIdxBuf = NULL;
	}
}

//=====================================================
//�`��
//=====================================================
void MeshField_Draw(void)
{
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�s��̓K�p
	D3DXMATRIX mtxWorld;
	D3DXMatrixTranslation(&mtxWorld, 0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���C�e�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//D3DMCS_COLOR1�͒��_�J���[, D3DMCS_MATERIAL�̓��f���J���[
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(���K��, ���邩���Ȃ���)
	//�A���r�G���g���C�g
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 255));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	//���b�s���O���[�h�̎w��
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�`��ݒ�
	pDevice->SetStreamSource(0, lpVtxBuf, 0, sizeof(MeshVertex));
	pDevice->SetIndices(lpIdxBuf);
	pDevice->SetFVF(FVF_MESH);								//�f�o�C�X�ɒ��_�f�[�^��n��
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));		//�e�N�X�`�����f�o�C�X�ɓn��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//FALSE:���C�gOFF TRUE:���C�gON
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_vertex_num - 2, 0, g_index_num - 2);

	//���C�e�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//D3DMCS_COLOR1�͒��_�J���[, D3DMCS_MATERIAL�̓��f���J���[
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(���K��, ���邩���Ȃ���)
	//�A���r�G���g���C�g
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}

//=====================================================
//�`��(�s��ݒ�)
//=====================================================
void MeshField_Draw(D3DXMATRIX world)
{
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�s��̓K�p
	pDevice->SetTransform(D3DTS_WORLD, &world);

	//���C�e�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//D3DMCS_COLOR1�͒��_�J���[, D3DMCS_MATERIAL�̓��f���J���[
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(���K��, ���邩���Ȃ���)
	//�A���r�G���g���C�g
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 255));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	//���b�s���O���[�h�̎w��
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�`��ݒ�
	pDevice->SetStreamSource(0, lpVtxBuf, 0, sizeof(MeshVertex));
	pDevice->SetIndices(lpIdxBuf);
	pDevice->SetFVF(FVF_MESH);								//�f�o�C�X�ɒ��_�f�[�^��n��
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));		//�e�N�X�`�����f�o�C�X�ɓn��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//FALSE:���C�gOFF TRUE:���C�gON
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_vertex_num - 2, 0, g_index_num - 2);

	//���C�e�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//D3DMCS_COLOR1�͒��_�J���[, D3DMCS_MATERIAL�̓��f���J���[
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(���K��, ���邩���Ȃ���)
	//�A���r�G���g���C�g
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}