#include "model.h"
#include "fbx_model.h"

//=====================================================
//マクロ定義
//=====================================================
#define MODEL_MAX (16)

//=====================================================
//構造体宣言
//=====================================================
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxScaling;
	bool isUse;
}STONE;

//=====================================================
//グローバル変数
//=====================================================
static int g_modelId = 0;
static STONE g_Stone[MODEL_MAX];

//=====================================================
//初期化
//=====================================================
void Model_Test_Init(void)
{
	g_modelId = Fbx_Model_Load("model\\stone\\a_test.fbx", "model\\stone\\");
	//for (int i = 0; i < MODEL_MAX; i++)
	//{
		g_Stone[0].isUse = true;
		D3DXMatrixIdentity(&g_Stone[0].mtxWorld);
		D3DXMatrixIdentity(&g_Stone[0].mtxScaling);

		D3DXMatrixTranslation(&g_Stone[0].mtxWorld, -5.0f, 1.0f, -5.0f);
		D3DXMatrixScaling(&g_Stone[0].mtxScaling, 2.0f, 2.0f, 2.0f);
		g_Stone[0].mtxWorld = g_Stone[0].mtxScaling * g_Stone[0].mtxWorld;
	//}
}

//=====================================================
//更新
//=====================================================
void Model_Test_Update(void)
{
	//for (int i = 0; i < MODEL_MAX; i++)
	//{
	//	if (!g_Stone[i].isUse)
	//	{
	//		continue;
	//	}
	//}
}

//=====================================================
//描画
//=====================================================
void Model_Test_Draw(void)
{
	//for (int i = 0; i < MODEL_MAX; i++)
	//{
		Fbx_Model_Draw(g_modelId, g_Stone[0].mtxWorld);
	//}
}