#include <d3dx9.h>
#include "mydirectx.h"
#include "camera.h"
#include "texture.h"

// �r���{�[�h��]�s��擾�֐�
//   BillPos    : �r���{�[�h�̐���_�̈ʒu
//   TargetPos  : �r���{�[�h�����������_
//   Rpt        : ��]�s��
//void GetBillBoardRotation(D3DXVECTOR3 *BillPos, D3DXVECTOR3 *TargetPos, D3DXMATRIX *Rot)
//{
//	D3DXMatrixIdentity(Rot);
//	D3DXMatrixLookAtLH(Rot, TargetPos, BillPos, &D3DXVECTOR3(0, 1, 0));
//	D3DXMatrixInverse(Rot, NULL, Rot);
//	Rot->_41 = 0.0f;   // �I�t�Z�b�g��؂�i��]�s�񂾂��ɂ��Ă��܂��j
//	Rot->_42 = 0.0f;
//	Rot->_43 = 0.0f;
//}

//====================================================
//�\���̐錾
//====================================================
typedef struct Billboard_Vertex_tag
{
	D3DXVECTOR3 position;	//���W
	D3DCOLOR color;			//�F���
	D3DXVECTOR2 UV;			//UV�l
}BillboardVertex;
#define FVF_BILLBOARD (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)//  | D3DFVF_NORMAL

//====================================================
//�O���[�o���ϐ�
//====================================================
static BillboardVertex g_billboard[] = 
{
	{D3DXVECTOR3(-0.5f, 0.5f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255) , D3DXVECTOR2(0.0f, 0.0f)},
	{D3DXVECTOR3(0.5f, 0.5f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255)  , D3DXVECTOR2(1.0f, 0.0f)},
	{D3DXVECTOR3(-0.5f, -0.5f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f)},
	{D3DXVECTOR3(0.5f, -0.5f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255) , D3DXVECTOR2(1.0f, 1.0f)}
};

static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX g_mtxInv;
static unsigned int g_tex = NULL;

//====================================================
//������
//====================================================
void billboard_Init(const char *filename)
{
	g_tex = Texture_SetLoadFile(filename, 128, 128);
}

//====================================================
//�`��
//====================================================
void billboard_Draw(void)
{
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMatrixIdentity(&g_mtxWorld);
	D3DXMatrixTranslation(&g_mtxWorld, 1.0f, 1.0f, 1.0f);

	D3DXMatrixIdentity(&g_mtxInv);
	D3DXMatrixInverse(&g_mtxInv, NULL, &Camera_GetView());
	g_mtxInv._41 = 0.0f;
	g_mtxInv._42 = 0.0f;
	g_mtxInv._43 = 0.0f;

	g_mtxWorld = g_mtxInv * g_mtxWorld;

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);

	//�`��ݒ�
	pDevice->SetFVF(FVF_BILLBOARD);					//�f�o�C�X�ɒ��_�f�[�^��n��
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));					//�e�N�X�`�����f�o�C�X�ɓn��
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//FALSE:���C�gOFF TRUE:���C�gON
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_billboard, sizeof(BillboardVertex));
}
