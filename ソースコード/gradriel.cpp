#include "model.h"
#include "fbx_model.h"

//=====================================================
//�}�N����`
//=====================================================
#define MODEL_MAX (16)

//=====================================================
//�\���̐錾
//=====================================================
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxScaling;
	bool isUse;
}GRADRIEL;

//=====================================================
//�O���[�o���ϐ�
//=====================================================
static int g_modelId = 0;
static GRADRIEL g_Gradriel[MODEL_MAX];

//=====================================================
//������
//=====================================================
void Gradriel_Init(void)
{
	g_modelId = Model_Load("model\\gradriel\\gradriel.x", "model\\gradriel\\");
	for (int i = 0; i < 2; i++)
	{
		g_Gradriel[i].isUse = true;
		D3DXMatrixIdentity(&g_Gradriel[i].mtxWorld);
		D3DXMatrixIdentity(&g_Gradriel[i].mtxScaling);

		D3DXMatrixTranslation(&g_Gradriel[i].mtxWorld, -5.0f + i * 10.0f, 1.0f, -5.0f);
		D3DXMatrixScaling(&g_Gradriel[i].mtxScaling, 2.0f, 2.0f, 2.0f);
		g_Gradriel[i].mtxWorld = g_Gradriel[i].mtxScaling * g_Gradriel[i].mtxWorld;
	}
}

//=====================================================
//�X�V
//=====================================================
void Gradriel_Update(void)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (!g_Gradriel[i].isUse)
		{
			continue;
		}
	}
}

//=====================================================
//�`��
//=====================================================
void Gradriel_Draw(void)
{
	for (int i = 0; i < MODEL_MAX; i++)
	{
		Model_Draw(g_modelId, g_Gradriel[i].mtxWorld);
	}
}