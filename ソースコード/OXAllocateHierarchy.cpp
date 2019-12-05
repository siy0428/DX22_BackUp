#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>
#include "OXAllocateHierarchy.h"
#include "mydirectx.h"
#include "texture.h"

static 	std::map<DWORD, D3DXMATRIX> g_combMatrixMap;
static OX::AllocateHierarchy g_allocater;
static OX::OXD3DXFRAME *g_pRootFrame = 0;
static ID3DXAnimationController *g_controller = 0;
static unsigned int g_tex;
D3DXBONECOMBINATION *g_combs;
OX::OXD3DXMESHCONTAINER *g_cont;

OX::OXD3DXMESHCONTAINER *getMeshContainer(D3DXFRAME *frame) {
	if (frame->pMeshContainer)
		return (OX::OXD3DXMESHCONTAINER*)frame->pMeshContainer;
	if (frame->pFrameFirstChild) {
		OX::OXD3DXMESHCONTAINER *mesh = getMeshContainer(frame->pFrameFirstChild);
		if (mesh != 0)
			return mesh;
	}
	if (frame->pFrameSibling)
		return getMeshContainer(frame->pFrameSibling);
	return 0;
}

void setFrameId(OX::OXD3DXFRAME *frame, ID3DXSkinInfo *info) {
	std::map<std::string, DWORD> nameToIdMap;
	for (DWORD i = 0; i < info->GetNumBones(); i++)
		nameToIdMap[info->GetBoneName(i)] = i;

	struct create {
		static void f(std::map<std::string, DWORD> nameToIdMap, ID3DXSkinInfo *info, OX::OXD3DXFRAME* frame) {
			if (nameToIdMap.find(frame->Name) != nameToIdMap.end()) {
				frame->id = nameToIdMap[frame->Name];
				frame->offsetMatrix = *info->GetBoneOffsetMatrix(frame->id);
			}
			if (frame->pFrameFirstChild)
				f(nameToIdMap, info, (OX::OXD3DXFRAME*)frame->pFrameFirstChild);
			if (frame->pFrameSibling)
				f(nameToIdMap, info, (OX::OXD3DXFRAME*)frame->pFrameSibling);
		}
	};
	create::f(nameToIdMap, info, frame);
}

void updateCombMatrix(std::map<DWORD, D3DXMATRIX> &combMatrixMap, OX::OXD3DXFRAME *frame) {
	struct update {
		static void f(std::map<DWORD, D3DXMATRIX> &combMatrixMap, D3DXMATRIX &parentBoneMatrix, OX::OXD3DXFRAME *frame) {
			D3DXMATRIX &localBoneMatrix = frame->TransformationMatrix;
			D3DXMATRIX boneMatrix = localBoneMatrix * parentBoneMatrix;
			if (frame->id != 0xffffffff)
				combMatrixMap[frame->id] = frame->offsetMatrix * boneMatrix;
			if (frame->pFrameFirstChild)
				f(combMatrixMap, boneMatrix, (OX::OXD3DXFRAME*)frame->pFrameFirstChild);
			if (frame->pFrameSibling)
				f(combMatrixMap, parentBoneMatrix, (OX::OXD3DXFRAME*)frame->pFrameSibling);
		}
	};
	D3DXMATRIX iden;
	D3DXMatrixIdentity(&iden);
	update::f(combMatrixMap, iden, frame);
}

void ModelAnime_Init(const char *filename, const char *texname)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スキンメッシュ情報をXファイルから取得
	D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, pDevice, &g_allocater, 0, (D3DXFRAME**)&g_pRootFrame, &g_controller);

	g_cont = getMeshContainer(g_pRootFrame);
	g_combs = (D3DXBONECOMBINATION*)g_cont->boneCombinationTable->GetBufferPointer();

	// フレーム内にボーンIDとオフセット行列を埋め込む
	setFrameId(g_pRootFrame, g_cont->pSkinInfo);
	//テクスチャ生成
	g_tex = Texture_SetLoadFile(texname, 0, 0);
}

void ModelAnime_Uninit(void)
{
	// スキンメッシュ情報削除
	g_allocater.DestroyFrame(g_pRootFrame);
}

void ModelAnime_Draw(float anime_speed)
{
	//デバイスのポインタ取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_controller->AdvanceTime(anime_speed, 0);
	updateCombMatrix(g_combMatrixMap, g_pRootFrame);

	pDevice->SetTexture(0, Texture_GetTexture(g_tex));
	for (DWORD i = 0; i < g_cont->numBoneCombinations; i++) {
		DWORD boneNum = 0;
		for (DWORD j = 0; j < g_cont->maxFaceInfl; j++) {
			DWORD id = g_combs[i].BoneId[j];
			if (id != UINT_MAX) {
				pDevice->SetTransform(D3DTS_WORLDMATRIX(j), &g_combMatrixMap[id]);
				boneNum++;
			}
		}
		pDevice->SetRenderState(D3DRS_VERTEXBLEND, boneNum - 1);
		g_cont->MeshData.pMesh->DrawSubset(i);
	}
}