/*===========================================================================
  @file   TPCamera.cpp
  @brief  ３人称視点カメラ
  @author HAL名古屋
  @date
===========================================================================*/
#include "TPCamera.h"
#include "Player.h"
#include "Quaternion.h"
#include "input.h"
using namespace DirectX;
// 定数
namespace {
	const Vector3f g_vEye(50.0f, 150.0f, -100.0f);
	const Vector3f g_vLook(0.0f, 0.0f, 0.0f);
	const Vector3f g_vUp(0.0f, 1.0f, 0.0f);
};
/*===========================================================================
  コンストラクタ
===========================================================================*/
TPCamera::TPCamera() :m_PlayerPos(nullptr)
{
	Init();
}
TPCamera::TPCamera(Vector3f* pos,XMFLOAT4X4* world):m_PlayerPos(pos),m_PlayerWorld(world)
{
	Init();
}
/*===========================================================================
  デストラクタ
===========================================================================*/
TPCamera::~TPCamera()
{
	
}
/*===========================================================================
  初期処理
===========================================================================*/
HRESULT TPCamera::Init()
{
	HRESULT hr = S_OK;
	m_vEye = Vector3f(0.0f, 0.0f, -50.0f);
	m_vLook = Vector3f(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3f(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(65);
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
	if (GetKeyPress(VK_UP))
	{

	}
	// 視点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(m_PlayerWorld);
	XMStoreFloat3(&m_vEye, XMVector3TransformCoord(
		XMLoadFloat3(&g_vEye), world));
	XMStoreFloat3(&m_vLook, XMVector3TransformCoord(
		XMLoadFloat3(&g_vLook), world));
	XMStoreFloat3(&m_vUp, XMVector3TransformNormal(
		XMLoadFloat3(&g_vUp), world));
	//-----------------------------------------------------------
	// 視点と注視点を移動、上方ベクトルを回転
	//XMMATRIX world = XMLoadFloat4x4(&pPlayer->GetWorld());
	//m_vLook = *m_PlayerPos;
	//
	//Vector3f axisY = Vector3f(1, 0, 0);
	//Vector3f axisXZ = Vector3f(1, 0, 1);
	//Vector3f vLookAt = m_vLook * 3;
	//// 横移動
	//axisY = axisY.Cross(GetAxisZ());
	//
	//if (GetKeyPress(VK_LSHIFT)) {
	//	m_vEye = RotateQuaternion(axisY, m_vEye, -RAD(1));
	//	
	//}
	//if (GetKeyPress(VK_RSHIFT)) {
	//	m_vEye = RotateQuaternion(axisY, m_vEye, RAD(1));
	//}
	//// ---縦移動---
	//axisXZ = m_vUp.Cross(GetAxisZ())*10;
	//
	//if (GetKeyPress(VK_I)) {
	//	m_vEye = RotateQuaternion(axisXZ, m_vEye, -RAD(1));
	//	m_vUp = RotateQuaternion(axisXZ, m_vUp, -RAD(1));
	//}
	//if (GetKeyPress(VK_K)) {
	//	m_vEye = RotateQuaternion(axisXZ, m_vEye, RAD(1));
	//	m_vUp = RotateQuaternion(axisXZ, m_vUp, RAD(1));
	//}
	/*m_vLook = pPlayer->GetPos();
	m_vEye += m_vLook;*/
	
	//-------------------------------------------------------------------------------------
	//XMVECTOR camera_pos, camera_up;
	//camera_pos = m_vEye - m_vLook;
	//camera_up = m_vUp;

	//XMVECTOR axis; //回転用軸
	////XZ軸回転用クオータニオン作成
	//axis = XMVector3Normalize(XMVector3Cross(m_vEye, m_vUp));
	//XMVECTOR qt_xz = XMQuaternionRotationAxis(axis, 
	//	XMConvertToRadians(GetDragDistance(MOUSEBUTTON_L).y)); //XMConvertToRadians(マウス移動量.y)
	////Y軸回転用クオータニオン作成
	//axis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMVECTOR qt_y = XMQuaternionRotationAxis(axis, 
	//	XMConvertToRadians(GetDragDistance(MOUSEBUTTON_L).x));//XMConvertToRadians(マウス移動量.x)
	////回転の掛け合わせ
	//XMVECTOR qt = XMQuaternionMultiply(qt_xz, qt_y);

	////カメラ回転
	//camera_pos = XMVector3Rotate(camera_pos, qt);
	//camera_pos += m_vLook;
	//m_vEye = camera_pos;
	////Upベクトル回転
	//camera_up = XMVector3Rotate(camera_up, qt);
	//m_vUp = camera_up;

	CCamera::Update();
}
