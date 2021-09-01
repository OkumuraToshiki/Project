/*===========================================================================
  @file   Camera.cpp
  @brief  �J�����̃x�[�X
  @author HAL���É�
  @date
  ->08/27 Draw()�֐�������
===========================================================================*/
#include "Camera.h"
#include "debugproc.h"
#include "input.h"

/*===========================================================================
   �ÓI�����o�ϐ�
===========================================================================*/
CCamera* CCamera::m_pCamera = nullptr;
Vector3f CCamera::m_vNowEye;	// ���݂̎��_
Vector3f CCamera::m_vNowLook;	// ���݂̒����_
Vector3f CCamera::m_vNowUp;		// ���݂̏���x�N�g��
/*===========================================================================
   �R���X�g���N�^
===========================================================================*/
CCamera::CCamera()
{
	m_vEye = Vector3f(0.0f, 100.0f, -100.0f);
	m_vLook = Vector3f(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3f(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	m_vNowEye = m_vEye;
	m_vNowLook = m_vLook;
	m_vNowUp = m_vUp;
	for (int i = 0; i < 6; ++i)
	{
		m_frusW[i] = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Update();
}
/*===========================================================================
   �f�X�g���N�^
===========================================================================*/
CCamera::~CCamera()
{
}
/*===========================================================================
   ������
===========================================================================*/
HRESULT CCamera::Init()
{
	HRESULT hr = S_OK;
	m_vEye = Vector3f(0.0f, 100.0f, -100.0f);
	m_vLook = Vector3f(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3f(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	m_vNowEye = m_vEye;
	m_vNowLook = m_vLook;
	m_vNowUp = m_vUp;
	for (int i = 0; i < 6; ++i)
	{
		m_frusW[i] = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	
	Update();
	return hr;
}

/*===========================================================================
   �I��
===========================================================================*/
void CCamera::Uninit()
{
	
}

/*===========================================================================
   �X�V
===========================================================================*/
void CCamera::Update()
{
	// ���_�A�����_�A����x�N�g�����߂Â���
	m_vNowEye.x = m_vNowEye.x * 0.8f + m_vEye.x * 0.2f;
	m_vNowEye.y = m_vNowEye.y * 0.8f + m_vEye.y * 0.2f;
	m_vNowEye.z = m_vNowEye.z * 0.8f + m_vEye.z * 0.2f;
	m_vNowLook.x = m_vNowLook.x * 0.8f + m_vLook.x * 0.2f;
	m_vNowLook.y = m_vNowLook.y * 0.8f + m_vLook.y * 0.2f;
	m_vNowLook.z = m_vNowLook.z * 0.8f + m_vLook.z * 0.2f;
	m_vNowUp.x = m_vNowUp.x * 0.8f + m_vUp.x * 0.2f;
	m_vNowUp.y = m_vNowUp.y * 0.8f + m_vUp.y * 0.2f;
	m_vNowUp.z = m_vNowUp.z * 0.8f + m_vUp.z * 0.2f;
	XMStoreFloat3(&m_vNowUp,
		XMVector3Normalize(XMLoadFloat3(&m_vNowUp)));
	// �r���[�ϊ��X�V
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vNowEye),
		XMLoadFloat3(&m_vNowLook),
		XMLoadFloat3(&m_vNowUp)));
	// �ˉe�ϊ��X�V
	XMStoreFloat4x4(&m_mProj,
		XMMatrixPerspectiveFovLH(m_fFOVY, m_fAspect,
			m_fNearZ, m_fFarZ));


	PrintDebugProc("���:%f %f %f\n", m_vEye.x, m_vEye.y, m_vEye.z);
}/*===========================================================================
    //������Ƃ̌�������  (���E���g�p)
    //�����@pCenter->���f���̒��S�AfRadius->���f���̔��a
	//�߂�l 0��\�� 1�����\�� 2�\��
===========================================================================*/
int CCamera::CollisionViewFrustum(Vector3f* pCenter, float fRadius)
{
	bool bHit = false;
	XMVECTOR frusw, center, dot;

	float fDot;
	center = XMLoadFloat3(pCenter);
	for (int i = 0; i < 6; ++i)
	{
		frusw = XMLoadFloat4(&m_frusW[i]);
		dot = XMPlaneDotCoord(frusw, center);
		XMStoreFloat(&fDot, dot);
		if (fDot < -fRadius)return 0;//���S�ɊO
		if (fDot <= fRadius)bHit = true;
	}
	if (bHit) return-1;//�ʂ��ׂ�
	return 1;//���S�ɓ���
}
/*===========================================================================
  
===========================================================================*/
XMMATRIX CCamera::GetCameraMatrix(Vector3f vLook, Vector3f vEye,Vector3f vUp)
{
	Vector3f forward, right, up;
	XMVECTOR vF, vR, vU;
	XMFLOAT4X4 world;
	XMMATRIX mW = XMMatrixIdentity();
	//�J����Z�������߂�
	forward.x = vLook.x - vEye.x;
	forward.y = vLook.y - vEye.y;
	forward.z = vLook.z - vEye.z;

	vF = XMLoadFloat3(&forward);
	vF = XMVector3Normalize(vF);
	XMStoreFloat3(&forward, vF);

	//�J����X�������߂�
	vU = XMLoadFloat3(&vUp);
	vR = XMVector3Cross(vU, vF);
	vR = XMVector3Normalize(vR);
	XMStoreFloat3(&right, vR);

	//�J����Y�������߂�
	vU = XMVector3Cross(vF, vR);
	vU = XMVector3Normalize(vU);
	XMStoreFloat3(&up, vU);

	//�J�����̃��[���h�ϊ��}�g���b�N�X�����߂�
	world._11 = right.x;
	world._12 = right.y;
	world._13 = right.z;
	world._14 = 0.0f;
	world._21 = up.x;
	world._22 = up.y;
	world._23 = up.z;
	world._24 = 0.0f;
	world._31 = forward.x;
	world._32 = forward.y;
	world._33 = forward.z;
	world._34 = 0.0f;

	world._41 = vEye.x;
	world._42 = vEye.y;
	world._43 = vEye.z;
	world._44 = 1.0f;

	mW = XMLoadFloat4x4(&world);
	return mW;
}
/*===========================================================================
   //�t�ˉe�s��v�Z
===========================================================================*/
Vector3f CCamera::UnProjection(const Vector3f& screenP)
{
	Vector3f vDev = Vector3f(screenP.x, screenP.y, screenP.z);
	vDev.x /= SCREEN_WIDTH * 0.5f;
	vDev.y /= SCREEN_HEIGHT * 0.5f;

	//�t�ˉe
	XMMATRIX   mtxUnpro;
	//XMFLOAT4X4 unproject;
	mtxUnpro = XMLoadFloat4x4(&m_mView) * XMLoadFloat4x4(&m_mProj);
	XMMatrixInverse(&XMLoadFloat3(&vDev), mtxUnpro);
	//���K��
	XMVECTOR xmv = XMVector3Normalize(XMLoadFloat3(&vDev));
	XMStoreFloat3(&vDev, xmv);
	return vDev;
}
/*===========================================================================
   �X�N���[���������
===========================================================================*/
void CCamera::GetScreenDirection(Vector3f& Start, Vector3f& Dir)
{
	XMFLOAT2 vPos = GetMousePos();
	Vector3f vS = Vector3f(vPos.x, vPos.y, 0.0f);
	Start = UnProjection(vS);

	vS.z = 0.9f;
	Vector3f vE = UnProjection(vS);

	//�����x�N�g��
	Dir.x = vE.x - Start.x;
	Dir.y = vE.y - Start.y;
	Dir.z = vE.z - Start.z;
	//���K��
	XMVECTOR xmv = XMVector3Normalize(XMLoadFloat3(&Dir));
	XMStoreFloat3(&Dir, xmv);
}
/*===========================================================================
  //�����x�N�g��
===========================================================================*/
Vector3f CCamera::FPVector()
{

	XMVECTOR vVec = XMVectorSet(m_vNowLook.x - m_vNowEye.x,
		m_vNowLook.y - m_vNowEye.y,
		m_vNowLook.z - m_vNowEye.z, 0.0f);
	vVec = XMVector3Normalize(vVec);
	Vector3f vDir;
	XMStoreFloat3(&vDir, vVec);
	PrintDebugProc("�޸��:%f,%f,%f\n", vDir.x, vDir.y, vDir.z);
	return vDir;
}