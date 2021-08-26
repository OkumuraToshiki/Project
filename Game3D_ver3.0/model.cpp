//=============================================================================
//
// ���f������ [model.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "model.h"
#include "main.h"
#include "FbxModel.h"
#include "input.h"
#include "debugproc.h"
#include "Camera.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_ICE01		"data/model/iceBall01.fbx"	// �t�@�C���P
#define MODEL_ICE02		"data/model/iceBall02.fbx"	// �t�@�C���Q
#define VIEW_ANGLE		XMConvertToRadians(45.0f)
#define VIEW_ASPECT		((float)SCREEN_WIDTH/SCREEN_HEIGHT)
#define VIEW_NEAR_Z		(10.0f)
#define VIEW_FAR_Z		(1000.0f)

#define VALUE_MOVE		(5.0f)
#define VALUE_ROTATE	(XM_PI*0.02f)

#define LIGHT0_DIFFUSE	XMFLOAT4(1.f,0.0f,0.0f,1.2f)
#define LIGHT0_AMBIENT	XMFLOAT4(1.0f,1.0f,0.2f,1.2f)
#define LIGHT0_SPECULAR	XMFLOAT4(1.0f,1.0f,1.0f,1.2f)
#define LIGHT0_DIR		XMFLOAT3(0.2f,1.0f,10.0f)

// �\���̒�`
typedef struct _tObject
{
	int			status;				// �X�e�[�^�X
	XMFLOAT3	pos;				// ���W
	XMFLOAT3	rot;				// �p�x
	XMFLOAT3	scale;				// �g�嗦
	XMMATRIX	matrix;				// �ϊ��}�g���b�N�X
	int			morph_count;		// ���[�t�B���O�v�Z�p���ԃJ�E���g�l
	int			morph_dir;			// ���[�t�B���O�̕���(0:������ 1:�t����)
	int			morph_time[2];		// ���[�t�B���O�̃L�[�t���[��

	int*		pIndex;				// �C���f�b�N�X�o�b�t�@�ێ��p
	TFbxVertex*	pVertex[2];			// �o�[�e�b�N�X�o�b�t�@�ێ��p
	TFbxVertex*	pVertexWk;			// �o�[�e�b�N�X�o�b�t�@��Ɨp
	int			nVertex;			// ���_���ێ��p
}tObject;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void InitLight(void);
//XMVECTOR Screenpos(XMVECTOR World_Pos);
XMVECTOR GetRay(XMVECTOR pos, float fRadius);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CFbxModel*			g_pModel;
XMFLOAT4X4			g_mtxWorld;

CFbxLight			g_light;

tObject				g_Object;	// ���[�t�B���O�I�u�W�F�N�g

//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// �J�����̏�����
	//InitCamera();

	// ���C�g�̏�����
	InitLight();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Object.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object.rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object.scale = XMFLOAT3(0.1f, 0.1f, 0.1f);

	// ���̑������l
	g_Object.status = 0;
	g_Object.morph_time[0] = 0;	// �P�߂̃��[�t�B���O����
	g_Object.morph_time[1] = 60;	// �Q�߂̃��[�t�B���O����
	g_Object.morph_dir = 0;	// ������
	g_Object.morph_count = 0;
	g_Object.nVertex = 0;

	// FBX�t�@�C���̓ǂݍ��݂P
	g_pModel = new CFbxModel();
	hr = g_pModel->Init(pDevice, pDeviceContext, MODEL_ICE01);
	if (SUCCEEDED(hr)) {
		g_pModel->SetCamera(CCamera::Get()->GetEye());
		g_pModel->SetLight(g_light);
	}

	// ���_�z��A�C���f�b�N�X�z��擾
	g_Object.nVertex = g_pModel->GetVertexCount();
	int nIndex = g_pModel->GetIndexCount();
	if (g_Object.nVertex <= 0 || nIndex <= 0) return E_FAIL;
	g_Object.pVertex[0] = new TFbxVertex[g_Object.nVertex];
	g_Object.pVertexWk = new TFbxVertex[g_Object.nVertex];
	g_Object.pIndex = new int[nIndex];
	if (g_pModel->GetVertex(g_Object.pVertex[0], g_Object.nVertex) != g_Object.nVertex
		|| g_pModel->GetIndex(g_Object.pIndex, nIndex) != nIndex) {
		delete[] g_Object.pIndex;
		delete[] g_Object.pVertex[0];
		delete[] g_Object.pVertexWk;
		return E_FAIL;
	}

	// FBX�t�@�C���̓ǂݍ��݂Q
	CFbxModel* pModel = new CFbxModel();
	hr = pModel->Init(pDevice, pDeviceContext, MODEL_ICE02);
	if (FAILED(hr)) return hr;

	// ���_�z��A�C���f�b�N�X�z��擾
	int nVertex = pModel->GetVertexCount();
	nIndex = pModel->GetIndexCount();
	if (nVertex <= 0 || nIndex <= 0) return E_FAIL;
	g_Object.pVertex[1] = new TFbxVertex[nVertex];
//	g_Object.pIndex = new int[nIndex];	// ���f���P�Ɠ����͂��Ȃ̂ŗp�ӂ��Ȃ�
	if (pModel->GetVertex(g_Object.pVertex[1], nVertex) != nVertex
		|| pModel->GetIndex(g_Object.pIndex, nIndex) != nIndex) {
		delete[] g_Object.pIndex;
		delete[] g_Object.pVertex[0];
		delete[] g_Object.pVertex[1];
		delete[] g_Object.pVertexWk;
		return E_FAIL;
	}

	// �f�[�^�擾�pFBX�t�@�C���̉��
	SAFE_DELETE(pModel);

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	// ���_�z��A�C���f�b�N�X�z����
	delete[] g_Object.pIndex;
	delete[] g_Object.pVertex[0];
	delete[] g_Object.pVertex[1];
	delete[] g_Object.pVertexWk;

	// FBX�t�@�C���̉��
	SAFE_DELETE(g_pModel);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	if (GetKeyPress(VK_A)) {
		g_Object.rot.x -= VALUE_ROTATE;
	}
	if (GetKeyPress(VK_D)) {
		g_Object.rot.x += VALUE_ROTATE;
	}
	if (GetKeyPress(VK_W)) {
		g_Object.rot.z += VALUE_ROTATE;
	}
	if (GetKeyPress(VK_S)) {
		g_Object.rot.z -= VALUE_ROTATE;
	}
	if (GetKeyPress(VK_Q)) {
		g_Object.rot.y -= VALUE_ROTATE;
	}
	if (GetKeyPress(VK_E)) {
		g_Object.rot.y += VALUE_ROTATE;
	}

	// ��ԕύX
	if (GetKeyTrigger(VK_1))
	{
		g_Object.status = 0;
	}
	else if (GetKeyTrigger(VK_2))
	{
		g_Object.status = 1;
	}
	else if (GetKeyTrigger(VK_3))
	{
		g_Object.status = 2;
	}


	// ���_���̌v�Z
	switch (g_Object.status)
	{
	case 0:
		memcpy_s(g_Object.pVertexWk, sizeof(TFbxVertex)*g_Object.nVertex, g_Object.pVertex[0], sizeof(TFbxVertex)*g_Object.nVertex);
		g_pModel->SetVertex(g_Object.pVertexWk, g_Object.nVertex);
		g_Object.status += 10;
		break;
	case 1:
		memcpy_s(g_Object.pVertexWk, sizeof(TFbxVertex)*g_Object.nVertex, g_Object.pVertex[1], sizeof(TFbxVertex)*g_Object.nVertex);
		g_pModel->SetVertex(g_Object.pVertexWk, g_Object.nVertex);
		g_Object.status += 10;
		break;
	case 2:
		// �i�s�������v�Z
		float ratio = (float)(g_Object.morph_count - g_Object.morph_time[0]) /
			(float)(g_Object.morph_time[1] - g_Object.morph_time[0]);
		// ���_���ɔ��f
		for (int i = 0; i < g_Object.nVertex; i++)
		{
			g_Object.pVertexWk[i].vPos.x = g_Object.pVertex[0][i].vPos.x+
				(g_Object.pVertex[1][i].vPos.x- g_Object.pVertex[0][i].vPos.x)*ratio;
			g_Object.pVertexWk[i].vPos.y = g_Object.pVertex[0][i].vPos.y+
				(g_Object.pVertex[1][i].vPos.y - g_Object.pVertex[0][i].vPos.y)*ratio;
			g_Object.pVertexWk[i].vPos.z = g_Object.pVertex[0][i].vPos.z+
				(g_Object.pVertex[1][i].vPos.z - g_Object.pVertex[0][i].vPos.z)*ratio;
		}
		// �v�Z�������_�����Z�b�g
		g_pModel->SetVertex(g_Object.pVertexWk, g_Object.nVertex);

		// �����̕ύX
		switch (g_Object.morph_dir)
		{
		case 0:
			g_Object.morph_count +=10;
			if (g_Object.morph_count >= g_Object.morph_time[1])
			{
				g_Object.morph_dir = 1;
			}
			
			break;
		case 1:
			g_Object.morph_count -=2;
			if (g_Object.morph_count <= g_Object.morph_time[0])
			{
				g_Object.morph_dir = 0;
			}
			
			break;
		}
		
		PrintDebugProc("MorphingCount:%d\n\n", g_Object.morph_count);
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	// �r���[�}�g���b�N�X�̍쐬
	//XMStoreFloat4x4(&g_mtxView,
	//	XMMatrixLookAtLH(
	//		XMVectorSet(g_posCameraP.x, g_posCameraP.y, g_posCameraP.z, 1.0f),
	//		XMVectorSet(g_posCameraR.x, g_posCameraR.y, g_posCameraR.z, 1.0f),
	//		XMVectorSet(g_vecCameraU.x, g_vecCameraU.y, g_vecCameraU.z, 0.0f)));

	//// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	//XMStoreFloat4x4(&g_mtxProjection,
	//	XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z));

	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	// �X�P�[���𔽉f
	mtxScl = XMMatrixScaling(g_Object.scale.x, g_Object.scale.y, g_Object.scale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// ��]�𔽉f
	mtxRot = XMMatrixRotationRollPitchYaw(g_Object.rot.x, g_Object.rot.y, g_Object.rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(g_Object.pos.x, g_Object.pos.y, g_Object.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	XMStoreFloat4x4(&g_mtxWorld, mtxWorld);

	// FBX�t�@�C���\��
	g_pModel->Render(g_mtxWorld, CCamera::Get()->GetView(), CCamera::Get()->GetProj(), eOpacityOnly);
	SetZWrite(false);
	g_pModel->Render(g_mtxWorld, CCamera::Get()->GetView(), CCamera::Get()->GetProj(), eTransparentOnly);
	SetZWrite(true);
}

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	/*g_posCameraP = XMFLOAT3(POS_CAMERA_P_X, POS_CAMERA_P_Y, POS_CAMERA_P_Z);
	g_posCameraR = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_vecCameraU = XMFLOAT3(0.0f, 1.0f, 0.0f);*/
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	XMStoreFloat3(&g_light.m_direction, XMVector3Normalize(XMLoadFloat3(&LIGHT0_DIR)));
	g_light.m_diffuse = LIGHT0_DIFFUSE;
	g_light.m_ambient = LIGHT0_AMBIENT;
	g_light.m_specular = LIGHT0_SPECULAR;
}
