#include <d3dx9.h>
#include "mydirectx.h"
#include "camera.h"
#include "texture.h"

// ビルボード回転行列取得関数
//   BillPos    : ビルボードの制御点の位置
//   TargetPos  : ビルボードが向く注視点
//   Rpt        : 回転行列
//void GetBillBoardRotation(D3DXVECTOR3 *BillPos, D3DXVECTOR3 *TargetPos, D3DXMATRIX *Rot)
//{
//	D3DXMatrixIdentity(Rot);
//	D3DXMatrixLookAtLH(Rot, TargetPos, BillPos, &D3DXVECTOR3(0, 1, 0));
//	D3DXMatrixInverse(Rot, NULL, Rot);
//	Rot->_41 = 0.0f;   // オフセットを切る（回転行列だけにしてしまう）
//	Rot->_42 = 0.0f;
//	Rot->_43 = 0.0f;
//}

//====================================================
//構造体宣言
//====================================================
typedef struct Billboard_Vertex_tag
{
	D3DXVECTOR3 position;	//座標
	D3DCOLOR color;			//色情報
	D3DXVECTOR2 UV;			//UV値
}BillboardVertex;
#define FVF_BILLBOARD (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)//  | D3DFVF_NORMAL

//====================================================
//グローバル変数
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
//初期化
//====================================================
void billboard_Init(const char *filename)
{
	g_tex = Texture_SetLoadFile(filename, 128, 128);
}

//====================================================
//描画
//====================================================
void billboard_Draw(void)
{
	//デバイスのポインタ取得
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

	//描画設定
	pDevice->SetFVF(FVF_BILLBOARD);					//デバイスに頂点データを渡す
	pDevice->SetTexture(0, Texture_GetTexture(g_tex));					//テクスチャをデバイスに渡す
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	//FALSE:ライトOFF TRUE:ライトON
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_billboard, sizeof(BillboardVertex));
}
