#include "texture.h"
#include "number.h"
#include "score.h"
#include "sound.h"
#include "debug.h"
#include "debug_font.h"
#include "game.h"
#include "fade.h"
#include "Efect.h"
#include "cube.h"
#include "grid.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "horse.h"
#include "model.h"
#include "gradriel.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "mydirectx.h"
#include "billboard.h"

//=====================================================
//�O���[�o���ϐ�
//=====================================================
static SCENE g_Scene = SCENE_NONE;
static bool g_TexLoad = true;
static HWND g_hwnd = NULL;
static bool g_j = true;

//=====================================================
//������
//=====================================================
void Game_Init(HWND hwnd)
{
	g_Scene = SCENE_3D;
	g_hwnd = hwnd;
	Number_Init();
	Score_Init();
	Debug_Init();
	Fade_init();
	EfectInit();
	Cube_Init();
	Grid_Init();
	Camera_Init();
	Horse_Init();
	Gradriel_Init();
	MeshField_Init(8, 8, Texture_SetLoadFile("Texture\\f_mesh.jpg", 1300, 866));
	MeshWall_Init(10, 5, Texture_SetLoadFile("Texture\\f_mesh.jpg", 1300, 866));
	billboard_Init("Texture\\tree000.png");
	if (g_TexLoad)
	{
		if (Texture_Load() > 0)
		{
			MessageBox(hwnd, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[", MB_OK);
		}
		g_TexLoad = false;
	}
}

//=====================================================
//�I��
//=====================================================
void Game_Uninit(void)
{
	Debug_Uninit();
	Fade_Uninit();
	EfectUninit();
	Grid_Uninit();
	Cube_Uninit();
	Model_Uninit();
	MeshField_Uninit();
	MeshWall_Uninit();
}

//=====================================================
//�X�V
//=====================================================
void Game_Update(void)
{
	//�f�o�C�X�̃|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�L�[�{�[�h�X�V
	Keyboard_Update();

	//���C���[�t���[���؂�ւ�
	if (Keyboard_IsTrigger(DIK_J))
	{
		g_j = !g_j;
	}
	//�\���b�h
	if (g_j)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	//���C���[�t���[��
	else
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//�V�[���J��
	switch (g_Scene)
	{
	case SCENE_3D:
		//�J�����ݒ�
		Camera_Set();
		Light_Set();
		Horse_Update();
		Gradriel_Update();
		break;
	default:
		break;
	}
}

//=====================================================
//�`��
//=====================================================
void Game_Draw(void)
{
	D3DXMATRIX mtxWorld[2], mtxRot[2];
	for (int i = 0; i < 2; i++)
	{
		D3DXMatrixIdentity(&mtxWorld[i]);
		D3DXMatrixIdentity(&mtxRot[i]);
	}

	//�ړ�
	D3DXMatrixTranslation(&mtxWorld[0], 5.0f, 0.0f, 5.0f);
	D3DXMatrixTranslation(&mtxWorld[1], -5.0f, 0.0f, 5.0f);

	//��]
	D3DXMatrixRotationY(&mtxRot[0], 45 * D3DX_PI / 180);
	D3DXMatrixRotationY(&mtxRot[1], -45 * D3DX_PI / 180);

	//�s�񍇐�
	mtxWorld[0] = mtxRot[0] * mtxWorld[0];
	mtxWorld[1] = mtxRot[1] * mtxWorld[1];

	switch (g_Scene)
	{
	case SCENE_3D:
		//�J�������o��
		Camera_Debug_Info();
		Grid_Draw();
		//Cube_jyugyou();
		//Horse_Draw();
		//Gradriel_Draw();
		//MeshField_Draw();
		//MeshWall_Draw(mtxWorld[0]);
		//MeshWall_Draw(mtxWorld[1]);
		billboard_Draw();
		break;
	}
}

//=====================================================
//�V�[���̐؂�ւ�
//=====================================================
void Game_SceneChange(SCENE scene)
{
	g_Scene = scene;
}

//=====================================================
//�V�[���̎擾
//=====================================================
SCENE Game_GetScene(void)
{
	return g_Scene;
}

//=====================================================
//�E�B���h�E�n���h���̎擾
//=====================================================
HWND Game_GetHwnd(void)
{
	return g_hwnd;
}