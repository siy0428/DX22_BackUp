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
//グローバル変数
//=====================================================
static SCENE g_Scene = SCENE_NONE;
static bool g_TexLoad = true;
static HWND g_hwnd = NULL;
static bool g_j = true;

//=====================================================
//初期化
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
			MessageBox(hwnd, "テクスチャが読み込めませんでした", "エラー", MB_OK);
		}
		g_TexLoad = false;
	}
}

//=====================================================
//終了
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
//更新
//=====================================================
void Game_Update(void)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//キーボード更新
	Keyboard_Update();

	//ワイヤーフレーム切り替え
	if (Keyboard_IsTrigger(DIK_J))
	{
		g_j = !g_j;
	}
	//ソリッド
	if (g_j)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	//ワイヤーフレーム
	else
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//シーン遷移
	switch (g_Scene)
	{
	case SCENE_3D:
		//カメラ設定
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
//描画
//=====================================================
void Game_Draw(void)
{
	D3DXMATRIX mtxWorld[2], mtxRot[2];
	for (int i = 0; i < 2; i++)
	{
		D3DXMatrixIdentity(&mtxWorld[i]);
		D3DXMatrixIdentity(&mtxRot[i]);
	}

	//移動
	D3DXMatrixTranslation(&mtxWorld[0], 5.0f, 0.0f, 5.0f);
	D3DXMatrixTranslation(&mtxWorld[1], -5.0f, 0.0f, 5.0f);

	//回転
	D3DXMatrixRotationY(&mtxRot[0], 45 * D3DX_PI / 180);
	D3DXMatrixRotationY(&mtxRot[1], -45 * D3DX_PI / 180);

	//行列合成
	mtxWorld[0] = mtxRot[0] * mtxWorld[0];
	mtxWorld[1] = mtxRot[1] * mtxWorld[1];

	switch (g_Scene)
	{
	case SCENE_3D:
		//カメラ情報出力
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
//シーンの切り替え
//=====================================================
void Game_SceneChange(SCENE scene)
{
	g_Scene = scene;
}

//=====================================================
//シーンの取得
//=====================================================
SCENE Game_GetScene(void)
{
	return g_Scene;
}

//=====================================================
//ウィンドウハンドルの取得
//=====================================================
HWND Game_GetHwnd(void)
{
	return g_hwnd;
}