#include "model.h"

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
}HORSE;

//=====================================================
//グローバル変数
//=====================================================
static int g_modelId = 0;
static HORSE g_Horse[MODEL_MAX];

//=====================================================
//初期化
//=====================================================
void Horse_Init(void)
{
	g_modelId = Model_Load("model\\cart\\cart.x", "model\\cart\\");

	for (int i = 0; i < 2; i++)
	{
		g_Horse[i].isUse = true;
		D3DXMatrixIdentity(&g_Horse[i].mtxWorld);
		D3DXMatrixIdentity(&g_Horse[i].mtxScaling);

		D3DXMatrixTranslation(&g_Horse[i].mtxWorld, -5.0f + i * 10.0f, 1.0f, 2.0f);
		D3DXMatrixScaling(&g_Horse[i].mtxScaling, 5.0f, 5.0f, 5.0f);
		g_Horse[i].mtxWorld = g_Horse[i].mtxScaling * g_Horse[i].mtxWorld;
	}
}

//=====================================================
//更新
//=====================================================
void Horse_Update(void)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (!g_Horse[i].isUse)
		{
			continue;
		}
	}
}

//=====================================================
//描画
//=====================================================
void Horse_Draw(void)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model_Draw(g_modelId, g_Horse[i].mtxWorld);
	}
}