/*===========================================================================
  @file   TPCamera.cpp
  @brief  ３人称視点カメラ
  @author HAL名古屋
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
  初期処理
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
  終了処理
===========================================================================*/
void TPCamera::Uninit()
{
}
/*===========================================================================
  更新処理
===========================================================================*/
void TPCamera::Update()
{
	// 視点と注視点を移動、上方ベクトルを回転
	//XMMATRIX world = XMLoadFloat4x4(&CPlayer::GetWorld());
	//XMStoreFloat3(&m_vEye, XMVector3TransformCoord(
	//	XMLoadFloat3(&g_vEye), world));
	//XMStoreFloat3(&m_vLook, XMVector3TransformCoord(
	//	XMLoadFloat3(&g_vLook), world));
	//XMStoreFloat3(&m_vUp, XMVector3TransformNormal(
	//	XMLoadFloat3(&g_vUp), world));
	//// 行列更新
	//CCamera::Update();
	/*if (GetKeyPress(VK_L))
	{
		m_vEye=RotateQuaternion()
	}*/
}
