/*===========================================================================
  @file   TPCamera.cpp
  @brief  �R�l�̎��_�J����
  @author HAL���É�
  @date
===========================================================================*/
#include "TPCamera.h"
#include "Player.h"
#include "Quaternion.h"
#include "input.h"
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
TPCamera::TPCamera() 
{
}
/*===========================================================================
  �f�X�g���N�^
===========================================================================*/
TPCamera::~TPCamera()
{
}
/*===========================================================================
  ��������
===========================================================================*/
HRESULT TPCamera::Init()
{
	HRESULT hr = S_OK;
	m_vEye = Vector3f(0.0f, 0.0f, -100.0f);
	m_vLook = Vector3f(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3f(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)(SCREEN_WIDTH / SCREEN_HEIGHT);
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	
	for (int i = 0; i < 6; ++i)
	{
		m_frusW[i] = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	return hr;
}
/*===========================================================================
  �I������
===========================================================================*/
void TPCamera::Uninit()
{
}
/*===========================================================================
  �X�V����
===========================================================================*/
void TPCamera::Update(PlayerClass* pPlayer)
{
	// ���_�ƒ����_���ړ��A����x�N�g������]
	XMMATRIX world = XMLoadFloat4x4(&pPlayer->GetWorld());
	//m_vLook = pPlayer->GetPos();
	
	Vector3f axis = Vector3f(0, 1, 0);
	// ---�c�ړ�---
	axis.x = m_vEye.y * m_vUp.z - m_vEye.z * m_vUp.y;
	axis.y = m_vEye.z * m_vUp.x - m_vEye.x * m_vUp.z;
	axis.z = m_vEye.x * m_vUp.y - m_vEye.y * m_vUp.x;
	if (GetKeyPress(VK_I)) {
		m_vEye = RotateQuaternion(axis, m_vEye, -RAD(1));
		m_vUp = RotateQuaternion(axis, m_vUp, -RAD(1));
	}
	if (GetKeyPress(VK_K)) {
		m_vEye = RotateQuaternion(axis, m_vEye, RAD(1));
		m_vUp = RotateQuaternion(axis, m_vUp, RAD(1));
	}
	CCamera::Update();
}
