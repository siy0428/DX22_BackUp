#include <d3dx9.h>
#include "mydirectx.h"
#include "common.h"
#include "debug_font.h"
#include "light.h"
#include "texture.h"

//====================================================
//構造体宣言
//====================================================
typedef struct Cube_Vertex_tag
{
	D3DXVECTOR3 position;	//座標
	D3DXVECTOR3 normal;		//法線ベクトル
	D3DCOLOR color;			//色情報
	D3DXVECTOR2 UV;			//テクスチャ
}CubeVertex;
#define FVF_CUBE (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)

//=====================================================
//グローバル変数
//=====================================================
static const CubeVertex g_cube_vertex[] = {						//頂点構造体

	////正面
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0.0f, 0.25f)},
	////{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	////右面
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	////{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	////{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	////左面
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f) },
	////奥面
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f)},
	////{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	////{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	////底面
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f),  D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	////{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	////{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.5f) },
	//上面
	{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.25f) },
	{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.5f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.5f)},
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f) }

	////正面
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0.0f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
	////右面
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f)},
	//{D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.0f) },
	////左面
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f),  D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f) },
	////奥面
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.0f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(1.0f, 0.25f)},
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.25f)},
	//{D3DXVECTOR3(0.5f, 0.5f, 0.5f),  D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.75f, 0.0f) },
	////底面
	//{D3DXVECTOR3(0.5f, -0.5f, 0.5f),  D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.25f) },
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f) },
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	//{D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.25f, 0.5f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.25f)},
	//{D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.5f, 0.5f) },
	////上面
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
static LPDIRECT3DVERTEXBUFFER9 lpVtxBuf;   // 頂点バッファ
static LPDIRECT3DINDEXBUFFER9 lpIdxBuf;    // 頂点インデックスバッファ

//=====================================================
//初期化
//=====================================================
void Cube_Init(void)
{
	g_tex = Texture_SetLoadFile("Texture\\spice_and_wolf.png", 1024, 1024);
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(24 * sizeof(g_cube_vertex), 0, (D3DFORMAT)FVF_CUBE, D3DPOOL_MANAGED, &lpVtxBuf, NULL);
	CubeVertex *vbuf;

	// ロック
	lpVtxBuf->Lock(0, 0, (void**)(&vbuf), D3DLOCK_NOSYSLOCK);
	// データの転送
	memcpy(vbuf, g_cube_vertex, 24 * sizeof(g_cube_vertex));
	// 解放
	lpVtxBuf->Unlock();

	pDevice->CreateIndexBuffer(36 * sizeof(CubeVertex), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &lpIdxBuf, NULL);

	// 確保する頂点インデックスバッファを宣言
	unsigned short*    ibuf;
	// ロック
	lpIdxBuf->Lock(0, 0, (void**)(&ibuf), D3DLOCK_NOSYSLOCK);
	// 頂点インデックスの確保
	for (int i = 0; i < 6; i++)
	{
		ibuf[0 + 6 * i] = 0 + 4 * i;
		ibuf[1 + 6 * i] = 1 + 4 * i;
		ibuf[2 + 6 * i] = 2 + 4 * i;
		ibuf[3 + 6 * i] = 1 + 4 * i;
		ibuf[4 + 6 * i] = 3 + 4 * i;
		ibuf[5 + 6 * i] = 2 + 4 * i;
	}

	// 解放
	lpIdxBuf->Unlock();

	// デバイスにインデックスをセット
	pDevice->SetIndices(lpIdxBuf);
}

//=====================================================
//終了
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
//描画
//=====================================================
void Cube_Draw(const D3DXMATRIX *pMtx)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//ライティング設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//D3DMCS_COLOR1は頂点カラー, D3DMCS_MATERIALはモデルカラー
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(正規化, するかしないか)
	//アンビエントライト
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	//描画設定
	pDevice->SetStreamSource(0, lpVtxBuf, 0, sizeof(CubeVertex));
	pDevice->SetIndices(lpIdxBuf);
	pDevice->SetFVF(FVF_CUBE);								//デバイスに頂点データを渡す
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));		//テクスチャをデバイスに渡す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//FALSE:ライトOFF TRUE:ライトON
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
	//ライティング設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//D3DMCS_COLOR1は頂点カラー, D3DMCS_MATERIALはモデルカラー
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(正規化, するかしないか)
	//アンビエントライト
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}

//=====================================================
//授業用
//=====================================================
void Cube_jyugyou(void)
{
	//ワールド座標変換
	D3DXMATRIX mtxWorld[8], mtxRotation[2][3], mtxTrans[8], mtxScaling[2];		//行列用変数
	for (int i = 0; i < 8; i++)
	{
		D3DXMatrixIdentity(&mtxWorld[i]);										//単位行列を作る
	}

	D3DXMatrixRotationX(&mtxRotation[0][0], 0 * D3DX_PI / 180);					//x軸回転
	D3DXMatrixRotationY(&mtxRotation[0][1], 0 * D3DX_PI / 180);					//y軸回転
	D3DXMatrixRotationZ(&mtxRotation[0][2], 0 * D3DX_PI / 180);					//z軸回転
	D3DXMatrixRotationY(&mtxRotation[1][1], g_angle * D3DX_PI / 180);			//y軸回転
	D3DXMatrixScaling(&mtxScaling[0], 1.0f, 1.0f, 1.0f);
	D3DXMatrixScaling(&mtxScaling[1], (FLOAT)sin(g_scale) + 2, (FLOAT)sin(g_scale) + 2, (FLOAT)sin(g_scale) + 2);
	D3DXMatrixTranslation(&mtxTrans[0], g_pos.x, g_pos.y, g_pos.z);				//平行移動
	D3DXMatrixTranslation(&mtxTrans[1], -4.5f, 0.5f, -4.5f);					//平行移動

	D3DXMatrixTranslation(&mtxTrans[2], 4.5f - (sin(g_scale) + 1) / 2, 0.5f + (sin(g_scale) + 1) / 2, 4.5f - (sin(g_scale) + 1) / 2);	//平行移動

	D3DXMatrixTranslation(&mtxTrans[3], -4.5f, g_fall[0], 4.5f);				//平行移動
	D3DXMatrixTranslation(&mtxTrans[4], -4.5f, g_fall[1], 4.5f);				//平行移動
	D3DXMatrixTranslation(&mtxTrans[5], -4.5f, g_fall[2], 4.5f);				//平行移動
	D3DXMatrixTranslation(&mtxTrans[6], -4.5f, g_fall[3], 4.5f);				//平行移動
	D3DXMatrixTranslation(&mtxTrans[7], -4.5f, g_fall[4], 4.5f);				//平行移動

	//DebugFont_Draw(0, 32, "sin補正値 = %.02lf", (sin(g_scale) + 1) / 2);

	g_scale += 0.05f;

	mtxWorld[0] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[0];		//行列の合成
	mtxWorld[1] = mtxScaling[0] * mtxRotation[1][1] * mtxTrans[1];												//行列の合成
	mtxWorld[2] = mtxScaling[1] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[2];		//行列の合成

	mtxWorld[3] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[3];		//行列の合成
	mtxWorld[4] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[4];		//行列の合成
	mtxWorld[5] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[5];		//行列の合成
	mtxWorld[6] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[6];		//行列の合成
	mtxWorld[7] = mtxScaling[0] * mtxRotation[0][0] * mtxRotation[0][1] * mtxRotation[0][2] * mtxTrans[7];		//行列の合成

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

	//積む処理
	//1個目
	if (g_fall[0] >= 0.5f)
	{
		g_fall[0] -= 0.1f;
	}
	//2個目
	else if (g_fall[1] >= 1.4f)
	{
		g_fall[1] -= 0.1f;
	}
	//3個目
	else if (g_fall[2] >= 2.3f)
	{
		g_fall[2] -= 0.1f;
	}
	//4個目
	else if (g_fall[3] >= 3.2f)
	{
		g_fall[3] -= 0.1f;
	}
	//5個目
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