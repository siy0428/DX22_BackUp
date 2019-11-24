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
#include "fbx_model.h"
#include "model_test.h"
#include "mesh.h"

//=====================================================
//�O���[�o���ϐ�
//=====================================================
static SCENE g_Scene = SCENE_NONE;
static bool g_TexLoad = true;
static HWND g_hwnd = NULL;

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
	//Model_Test_Init();
	Mesh_Init();
	if (g_TexLoad)
	{
		if (Texture_Load() > 0)
		{
			MessageBox(hwnd, "�e�N�X�`�����ǂݍ��߂܂���ł���", "�G���[", MB_OK);
			Game_Uninit();
			exit(0);
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
	//Model_Uninit();
	Mesh_Uninit();
}

//=====================================================
//�X�V
//=====================================================
void Game_Update(void)
{
	//�L�[�{�[�h�X�V
	Keyboard_Update();

	//�V�[���J��
	switch (g_Scene)
	{
	case SCENE_3D:
		//�J�����ݒ�
		Camera_Set();
		Light_Set();
		Horse_Update();
		Gradriel_Update();
		//Model_Test_Update();
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
	switch (g_Scene)
	{
	case SCENE_3D:
		//�J�������o��
		Camera_Debug_Info();
		//Cube_jyugyou();
		Grid_Draw();
		//Horse_Draw();
		//Gradriel_Draw();
		//Model_Test_Draw();
		Mesh_Draw();
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