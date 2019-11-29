#ifndef _MESH_WALL_H_
#define _MESH_WALL_H_

#include <d3dx9.h>

void MeshWall_Init(int width, int height, int texId);
void MeshWall_Uninit(void);
void MeshWall_Draw(D3DXMATRIX world);

#endif