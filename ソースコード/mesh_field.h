#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_

#include <d3dx9.h>

void MeshField_Init(int width, int height, int texId);
void MeshField_Uninit(void);
void MeshField_Draw(void);
void MeshField_Draw(D3DXMATRIX world);

#endif