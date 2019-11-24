#include <d3dx9.h>
#include "mydirectx.h"
#include "common.h"
#include "debug_font.h"
#include "light.h"
#include "texture.h"

//====================================================
//�\���̐錾
//====================================================
typedef struct Cube_Vertex_tag
{
	D3DXVECTOR3 position;	//���W
	D3DXVECTOR3 normal;		//�@���x�N�g��
	D3DCOLOR color;			//�F���
	D3DXVECTOR2 UV;			//�e�N�X�`��
}CubeVertex;
#define FVF_CUBE (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)

//=====================================================
//�O���[�o���ϐ�
//=====================================================
static const CubeVertex g_cube_vertex[] = {						//���_�\����

	////����
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0.0f, 0.25f)},
	////{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	////�E��
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	////{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	////{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	////����
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f) },
	////����
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	////{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	////���
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f),  D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	////{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	////{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.5f) },
	//���
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.25f) },
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.5f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.5f)},
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f) }

	////����
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0.0f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	////�E��
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	////����
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f) },
	////����
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f)},
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	////���
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f),  D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.5f) },
	////���
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.25f) },
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.5f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.5f)},
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f) }
};
static D3DXVECTOR3 g_pos = { 4.5f, 0.5f, -4.5f };
static short int g_state = 0;
static float g_angle = 0.0f;
static float g_scale = 0.0f;
static float g_fall[5] = {
	10.0f,
	10.0f,
	10.0f,
	10.0f,
	10.0f
};
static unsigned int g_tex = NULL;
static LPDIRECT3DVERTEXBUFFER9 lpVtxBuf;   // ���_�o�b�t�@
static LPDIRECT3DINDEXBUFFER9 lpIdxBuf;    // ���_�C���f�b�N�X�o�b�t�@

//=====================================================
//������
//=====================================================
void Cube_Init(void)
{
	g_tex = Texture_SetLoadFile("Texture\\spice_and_wolf.png", 1024, 1024);
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(24 * sizeof(g_cube_vertex), 0, (D3DFORMAT)FVF_CUBE, D3DPOOL_MANAGED, &lpVtxBuf, NULL);
	CubeVertex *vbuf;

	// ���b�N
	lpVtxBuf->Lock(0, 0, (void**)(&vbuf), D3DLOCK_NOSYSLOCK);
	// �f�[�^�̓]��
	memcpy(vbuf, g_cube_vertex, 24 * sizeof(g_cube_vertex));
	// ���
	lpVtxBuf->Unlock();

	pDevice->CreateIndexBuffer(36 * sizeof(CubeVertex), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &lpIdxBuf, NULL);

	// �m�ۂ��钸�_�C���f�b�N�X�o�b�t�@��錾
	unsigned short*    ibuf;
	// ���b�N
	lpIdxBuf->Lock(0, 0, (void**)(&ibuf), D3DLOCK_NOSYSLOCK);
	// ���_�C���f�b�N�X�̊m��
	for (int i = 0; i < 6; i++)
	{
		ibuf[0 + 6 * i] = 0 + 4 * i;
		ibuf[1 + 6 * i] = 1 + 4 * i;
		ibuf[2 + 6 * i] = 2 + 4 * i;
		ibuf[3 + 6 * i] = 1 + 4 * i;
		ibuf[4 + 6 * i] = 3 + 4 * i;
		ibuf[5 + 6 * i] = 2 + 4 * i;
	}

	// ���
	lpIdxBuf->Unlock();

	// �f�o�C�X�ɃC���f�b�N�X���Z�b�g
	pDevice->SetIndices(lpIdxBuf);
}

//=====================================================
//�I��
//=====================================================
void Cube_Uninit(void)
{
	Texture_Destroy();

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
void Cube_Draw(const D3DXMATRIX *pMtx)
{
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���C�e�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//D3DMCS_COLOR1�͒��_�J���[, D3DMCS_MATERIAL�̓��f���J���[
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(���K��, ���邩���Ȃ���)
	//�A���r�G���g���C�g
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	//�`��ݒ�
	pDevice->SetStreamSource(0, lpVtxBuf, 0, sizeof(CubeVertex));
	pDevice->SetIndices(lpIdxBuf);
	pDevice->SetFVF(FVF_CUBE);								//�f�o�C�X�ɒ��_�f�[�^��n��
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));		//�e�N�X�`�����f�o�C�X�ɓn��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//FALSE:���C�gOFF TRUE:���C�gON
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
	//���C�e�B���O�ݒ�
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//D3DMCS_COLOR1�͒��_�J���[, D3DMCS_MATERIAL�̓��f���J���[
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(���K��, ���邩���Ȃ���)
	//�A���r�G���g���C�g
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}

//=====================================================
//���Ɨp
//=====================================================
void Cube_jyugyou(void)
{
	//���[���h���W�ϊ�
	D3DXMATRIX mtxWorld[8], mtxRotation[2][3], mtxTrans[8], mtxScaling[2];		//�s��p�ϐ�
	for (int i = 0; i < 8; i++)
	{
		D3DXMatrixIdentity(&mtxWorld[i]);										//�P�ʍs������
	}

	D3DXMatrixRotationX(&mtxRotation[0][0], 0 * D3DX_PI / 180);					//x����]
	D3DXMatrixRotationY(&mtxRotation[0][1], 0 * D3DX_PI / 180);					//y����]
	D3DXMatrixRotationZ(&mtxRotation[0][2], 0 * D3DX_PI / 180);					//z����]
	D3DXMatrixRotationY(&mtxRotation[1][1], g_angle * D3DX_PI / 180);			//y����]
	D3DXMatrixScaling(&mtxScaling[0], 1.0f, 1.0f, 1.0f);
	D3DXMatrixScaling(&mtxScaling[1], (FLOAT)sin(g_scale) + 2, (FLOAT)sin(g_scale) + 2, (FLOAT)sin(g_scale) + 2);
	D3DXMatrixTranslation(&mtxTrans[0], g_pos.x, g_pos.y, g_pos.z);				//���s�ړ�
	D3DXMatrixTranslation(&mtxTrans[1], -4.5f, 0.5f, -4.5f);					//���s�ړ�

	D3DXMatrixTranslation(&mtxTrans[2], 4.5f - (sin(g_scale) + 1) / 2, 0.5f + (sin(g_scale) + 1) / 2, 4.5f - (sin(g_scale) + 1) / 2);	//���s�ړ�

	D3DXMatrixTranslation(&mtxTrans[3], -4.5f, g_fall[0], 4.5f);				//���s�ړ�
	D3DXMatrixTranslation(&mtxTrans[4], -4.5f, g_fall[1], 4.5f);				//���s�ړ�
	D3DXMatrixTranslation(&mtxTrans[5], -4.5f, g_fall[2], 4.5f);				//���s�ړ�
	D3DXMatrixTranslation(&mtxTrans[6], -4.5f, g_fall[3], 4.5f);				//���s�ړ�
	D3DXMatrixTranslation(&mtxTrans[7], -4.5f, g_fall[4], 4.5f);				//���s�ړ�

	//DebugFont_Draw(0, 32, "sin�␳�l = %.02lf", (sin(g_scale) + 1) / 2);

	g_scale += 0.05f;

	mtxWorld[0] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[0];		//�s��̍���
	mtxWorld[1] = mtxScaling[0] * mtxRotation[1][1] * mtxTrans[1];												//�s��̍���
	mtxWorld[2] = mtxScaling[1] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[2];		//�s��̍���

	mtxWorld[3] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[3];		//�s��̍���
	mtxWorld[4] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[4];		//�s��̍���
	mtxWorld[5] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[5];		//�s��̍���
	mtxWorld[6] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[6];		//�s��̍���
	mtxWorld[7] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[7];		//�s��̍���

	g_angle += 2.0f;

	switch (g_state)
	{
	case 0:
		g_pos.x -= 0.1f;
		if (g_pos.x < -4.4f)
		{
			g_state = 1;
		}
		break;
	case 1:
		g_pos.z += 0.1f;
		if (g_pos.z > 4.4f)
		{
			g_state = 2;
		}
		break;
	case 2:
		g_pos.x += 0.1f;
		if (g_pos.x > 4.4f)
		{
			g_state = 3;
		}
		break;
	case 3:
		g_pos.z -= 0.1f;
		if (g_pos.z < -4.4f)
		{
			g_state = 0;
		}
		break;
	}

	//�ςޏ���
	//1��
	if (g_fall[0] >= 0.5f)
	{
		g_fall[0] -= 0.1f;
	}
	//2��
	else if (g_fall[1] >= 1.4f)
	{
		g_fall[1] -= 0.1f;
	}
	//3��
	else if (g_fall[2] >= 2.3f)
	{
		g_fall[2] -= 0.1f;
	}
	//4��
	else if (g_fall[3] >= 3.2f)
	{
		g_fall[3] -= 0.1f;
	}
	//5��
	else if (g_fall[4] >= 4.1f)
	{
		g_fall[4] -= 0.1f;
		if (g_fall[4] < 4.1f)
		{
			for (int i = 0; i < 5; i++)
			{
				g_fall[i] = 10.0f;
			}
		}
	}

	Cube_Draw(&mtxWorld[0]);
	Cube_Draw(&mtxWorld[1]);
	Cube_Draw(&mtxWorld[2]);
	Cube_Draw(&mtxWorld[3]);	//1
	Cube_Draw(&mtxWorld[4]);	//2
	Cube_Draw(&mtxWorld[5]);	//3
	Cube_Draw(&mtxWorld[6]);	//4
	Cube_Draw(&mtxWorld[7]);	//5
}