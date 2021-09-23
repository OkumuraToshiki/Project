/*===========================================================================
  @file   Camera.cpp
  @brief  �J�����̃x�[�X
  @author HAL���É�
  @date   08/27->09/23�����䌩����
===========================================================================*/
#include "Camera.h"
#include "debugproc.h"
#include "input.h"

/*===========================================================================
   �ÓI�����o�ϐ�
===========================================================================*/
CCamera* CCamera::m_pCamera = nullptr;
Vector3f CCamera::m_vNowEye = Vector3f(0, 0, 0);    // ���݂̎��_
Vector3f CCamera::m_vNowLook = Vector3f(0, 0, 0);   // ���݂̒����_
Vector3f CCamera::m_vNowUp = Vector3f(0, 0, 0);     // ���݂̏���x�N�g��
/*===========================================================================
   �R���X�g���N�^
===========================================================================*/
CCamera::CCamera()
{
	Init();

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
	m_fViewAngle = 45.0f;
	m_fFovy = XMConvertToRadians(m_fViewAngle);
	m_fAspect = (float)(SCREEN_WIDTH / SCREEN_HEIGHT);
	m_fNearZ = 1.0f;
	m_fFarZ = 1000.0f;
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
	//���K��
	m_vNowUp.Normalize();
	
	// �r���[�ϊ��X�V
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(
		XMVECTOR(m_vNowEye),
		XMVECTOR(m_vNowLook),
		XMVECTOR(m_vNowUp)));
	// �ˉe�ϊ��X�V
	XMStoreFloat4x4(&m_mProj,
		XMMatrixPerspectiveFovLH(m_fFovy, m_fAspect,
			m_fNearZ, m_fFarZ));

	//������ݒ�
	SetFrustum();

	PrintDebugProc("Eye:%f %f %f\n", m_vEye.x, m_vEye.y, m_vEye.z);
	PrintDebugProc("Look:%f %f %f\n", m_vLook.x, m_vLook.y, m_vLook.z);
	PrintDebugProc("Up:%f %f %f\n", m_vUp.x, m_vUp.y, m_vUp.z);
}
/*===========================================================================
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
   //�J������Z�������߂�
===========================================================================*/
Vector3f CCamera::GetAxisZ()
{
	Vector3f forward;
	//�J����Z�������߂�
	forward = m_vLook - m_vEye;
	forward.Normalize();
	return forward;
}
/*===========================================================================
   ������ݒ�
===========================================================================*/
void CCamera::SetFrustum()
{
	//������̏㉺���E�̖@���x�N�g�������߂�
	XMFLOAT4 m_frus[6];//������ 0�� 1�� 2�� 3�E 4�O 5��
	float fTan = tanf(XMConvertToRadians(m_fViewAngle*0.5f));
	//�㉺
	m_frus[0] = XMFLOAT4(0, -1.0f, fTan, 0.0f);
	m_frus[1] = XMFLOAT4(0.0f, 1.0f, fTan, 0.0f);
	//���E
	fTan *= m_fAspect;//�A�X�y�N�g���������
	m_frus[2] = XMFLOAT4(1.0f, 0.0f, fTan, 0.0f);
	m_frus[3] = XMFLOAT4(-1.0f, 0.0f, fTan, 0.0f);
	//�O��
	m_frus[4] = XMFLOAT4(0.0f, 0.0f, 1.0, -m_fNearZ);
	m_frus[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, m_fFarZ);

	//���K��
	for (int i = 0; i < 4; ++i)
	{
		XMStoreFloat4(&m_frus[i],
			XMPlaneNormalize(XMLoadFloat4(&m_frus[i])));
	}
	//�J�����̈ړ��ɔ����A����������[���h�ϊ�
	XMMATRIX mW;
	mW = GetMatrix();
	//���ʂ����[���h��Ԃɔz�u
	mW = XMMatrixInverse(nullptr, mW);
	mW = XMMatrixTranspose(mW);
	for (int i = 0; i < 6; ++i)
	{
		XMStoreFloat4(&m_frusW[i],
			XMPlaneTransform(//�����[���h�}�g���b�N�X�́A�t�s��̓]�u�s���n��
				XMLoadFloat4(&m_frus[i]), mW));
	}
}
/*===========================================================================
  �J�����̃��[���h�ϊ��s������߂�
===========================================================================*/
XMMATRIX CCamera::GetMatrix()
{
	Vector3f forward, right, up;
	XMFLOAT4X4 world;
	XMMATRIX mW = XMMatrixIdentity();
	//�J����Z�������߂�
	forward = GetAxisZ();
	//�J����X�������߂�
	right = m_vUp.Cross(forward);
	right.Normalize();

	//�J����Y�������߂�
	up = forward.Cross(right);
	up.Normalize();

	//�}�g���b�N�X�����߂�
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

	world._41 = m_vEye.x;
	world._42 = m_vEye.y;
	world._43 = m_vEye.z;
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
	XMMatrixInverse(&XMVECTOR(vDev), mtxUnpro);
	//���K��
	vDev.Normalize();
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
	Dir.Normalize();
}
