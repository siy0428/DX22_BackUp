#ifndef _CAMERA_H_
#define _CAMERA_H_

void Camera_Init(void);
void Camera_Set(void);			//カメラ設定
void Camera_Debug_Info(void);	//カメラ情報
D3DXMATRIX Camera_GetView(void);

#endif