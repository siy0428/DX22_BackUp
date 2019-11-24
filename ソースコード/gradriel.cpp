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
}GRADRIEL;

//=====================================================
//グローバル変数
//=====================================================
static int g_modelId = 0;
static GRADRIEL g_Gradriel[MODEL_MAX];

//=====================================================
//初期化
//=====================================================
void Gradriel_Init(void)
{
	g_modelId = Model_Load("model\\gradriel\\gradriel.x", "model\\gradriel\\");
	for (int i = 0; i < 2; i++)
	{
		g_Gradriel[i].isUse = true;
		D3DXMatrixIdentity(&g_Gradriel[i].mtxWorld);
		D3DXMatrixIdentity(&g_Gradriel[i].mtxScaling);

		D3DXMatrixTranslation(&g_Gradriel[i].mtxWorld, -5.0f + i * 10.0f, 1.0f, -5.0f);
		D3DXMatrixScaling(&g_Gradriel[i].mtxScaling, 2.0f, 2.0f, 2.0f);
		g_Gradriel[i].mtxWorld = g_Gradriel[i].mtxScaling * g_Gradriel[i].mtxWorld;
	}
}

//=====================================================
//更新
//=====================================================
void Gradriel_Update(void)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (!g_Gradriel[i].isUse)
		{
			continue;
		}
	}
}

//=====================================================
//描画
//=====================================================
void Gradriel_Draw(void)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model_Draw(g_modelId, g_Gradriel[i].mtxWorld);
	}
}