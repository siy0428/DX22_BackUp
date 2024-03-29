#ifndef _FBX_MODEL_H_
#define _FBX_MODEL_H_

#include <d3dx9.h>

int Fbx_Model_Load(const char *filename, const char *path_name);
void Fbx_Model_Uninit(void);
void Fbx_Model_Draw(int modelId, D3DMATRIX mtxWorld);

#endif