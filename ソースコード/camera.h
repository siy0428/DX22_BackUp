#ifndef _CAMERA_H_
#define _CAMERA_H_

void Camera_Init(void);
void Camera_Set(void);			//�J�����ݒ�
void Camera_Debug_Info(void);	//�J�������
D3DXMATRIX Camera_GetView(void);

#endif