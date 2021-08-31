/*===========================================================================
  @file   TPCamera.cpp
  @brief  �R�l�̎��_�J����
  @author HAL���É�
  @date
===========================================================================*/
#include "TPCamera.h"
#include "Quaternion.h"
#include "input.h"
TPCamera::TPCamera()
{
}
TPCamera::~TPCamera()
{
}
/*===========================================================================
  ��������
===========================================================================*/
HRESULT TPCamera::Init()
{
	HRESULT hr = S_OK;
	m_vEye = XMFLOAT3(0.0f, 0.0f, -100.0f);
	m_vLook = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_vUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)(SCREEN_WIDTH / SCREEN_HEIGHT);
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	
	for (int i = 0; i < 6; ++i)
	{
		m_frusW[i] = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Update();
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
void TPCamera::Update()
{
	// ���_�ƒ����_���ړ��A����x�N�g������]
	//XMMATRIX world = XMLoadFloat4x4(&CPlayer::GetWorld());
	//XMStoreFloat3(&m_vEye, XMVector3TransformCoord(
	//	XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vLook, XMVector3TransformCoord(
	//	XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vUp, XMVector3TransformNormal(
	//	XMLoadFloat3(&g_vUp), world));
	//// �s��X�V
	//CCamera::Update();
	/*if (GetKeyPress(VK_L))
	{
		m_vEye=RotateQuaternion()
	}*/
}
