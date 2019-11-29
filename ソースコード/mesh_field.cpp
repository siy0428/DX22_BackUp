#include "mydirectx.h"
#include <d3dx9.h>
#include "texture.h"
#include "input.h"

//====================================================
//構造体宣言
//====================================================
typedef struct Mesh_Vertex_tag
{
	D3DXVECTOR3 position;	//座標
	D3DXVECTOR3 normal;		//法線ベクトル
	D3DCOLOR color;			//色情報
	D3DXVECTOR2 UV;			//テクスチャ
}MeshVertex;
#define FVF_MESH (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)

//====================================================
//グローバル変数
//====================================================
static MeshVertex g_mesh_vertex;
static LPDIRECT3DVERTEXBUFFER9 lpVtxBuf;   // 頂点バッファ
static LPDIRECT3DINDEXBUFFER9 lpIdxBuf;    // 頂点インデックスバッファ
static unsigned int g_tex = NULL;
static int g_width;
static int g_height;
static int g_vertex_num;
static int g_index_num;

//=====================================================
//初期化
//=====================================================
void MeshField_Init(int width, int height, int texId)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_width = width;	//幅
	g_height = height;	//高さ
	g_vertex_num = (width + 1) * (height + 1);	//頂点数
	g_index_num = g_vertex_num + (height - 1) * (width + 1) + (height - 1) * 2;	//インデックス数
	g_tex = texId;

	pDevice->CreateVertexBuffer(sizeof(MeshVertex) * g_vertex_num, 0, (D3DFORMAT)FVF_MESH, D3DPOOL_MANAGED, &lpVtxBuf, NULL);

	// ロック
	MeshVertex *vbuf;
	lpVtxBuf->Lock(0, 0, (void**)(&vbuf), D3DLOCK_NOSYSLOCK);

	//頂点データ初期化
	for (int i = 0; i < g_vertex_num; i++)
	{
		vbuf[i].position = D3DXVECTOR3((FLOAT)(i % (g_width + 1) - g_width / 2), 0.0f, (FLOAT)(-i / (g_width + 1)) + g_height / 2);
		vbuf[i].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vbuf[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		vbuf[i].UV = D3DXVECTOR2((FLOAT)(i % (g_width + 1)) - g_width / 2, (FLOAT)(-i / (g_width + 1)) + g_height / 2);
	}

	// 解放
	lpVtxBuf->Unlock();

	pDevice->CreateIndexBuffer(g_index_num * sizeof(MeshVertex), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &lpIdxBuf, NULL);

	// 確保する頂点インデックスバッファを宣言
	unsigned short*    ibuf;
	// ロック
	lpIdxBuf->Lock(0, 0, (void**)(&ibuf), D3DLOCK_NOSYSLOCK);

	// 頂点インデックスの確保
	unsigned short index_num = 0;	//縮退ポリゴンの設定が行われた回数
	for (unsigned short i = 0; i < g_index_num / 2; i++)
	{
		//縮退ポリゴン
		if ((g_width + 1) + (g_width + 2) * index_num == i && i != 0 && i != g_index_num / 2 && g_height > 1)
		{
			ibuf[i + i] = i - 1 - index_num;
			ibuf[i + i + 1] = (g_width + 1) + (i - index_num);
			index_num++;
		}
		//通常インデックス
		else
		{
			ibuf[i + i] = (g_width + 1) + (i - index_num);
			ibuf[i + i + 1] = (i - index_num);
		}
	}

	// 解放
	lpIdxBuf->Unlock();
}

//=====================================================
//終了
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
//描画
//=====================================================
void MeshField_Draw(void)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//行列の適用
	D3DXMATRIX mtxWorld;
	D3DXMatrixTranslation(&mtxWorld, 0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//ライティング設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//D3DMCS_COLOR1は頂点カラー, D3DMCS_MATERIALはモデルカラー
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(正規化, するかしないか)
	//アンビエントライト
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 255));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	//ラッピングモードの指定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//描画設定
	pDevice->SetStreamSource(0, lpVtxBuf, 0, sizeof(MeshVertex));
	pDevice->SetIndices(lpIdxBuf);
	pDevice->SetFVF(FVF_MESH);								//デバイスに頂点データを渡す
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));		//テクスチャをデバイスに渡す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//FALSE:ライトOFF TRUE:ライトON
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_vertex_num - 2, 0, g_index_num - 2);

	//ライティング設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//D3DMCS_COLOR1は頂点カラー, D3DMCS_MATERIALはモデルカラー
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(正規化, するかしないか)
	//アンビエントライト
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}

//=====================================================
//描画(行列設定)
//=====================================================
void MeshField_Draw(D3DXMATRIX world)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//行列の適用
	pDevice->SetTransform(D3DTS_WORLD, &world);

	//ライティング設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);	//D3DMCS_COLOR1は頂点カラー, D3DMCS_MATERIALはモデルカラー
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(正規化, するかしないか)
	//アンビエントライト
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 255));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	//ラッピングモードの指定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//描画設定
	pDevice->SetStreamSource(0, lpVtxBuf, 0, sizeof(MeshVertex));
	pDevice->SetIndices(lpIdxBuf);
	pDevice->SetFVF(FVF_MESH);								//デバイスに頂点データを渡す
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));		//テクスチャをデバイスに渡す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//FALSE:ライトOFF TRUE:ライトON
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_vertex_num - 2, 0, g_index_num - 2);

	//ライティング設定
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//D3DMCS_COLOR1は頂点カラー, D3DMCS_MATERIALはモデルカラー
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);					//(正規化, するかしないか)
	//アンビエントライト
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(167, 98, 100));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
}