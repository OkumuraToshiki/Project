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
using namespace DirectX;
// �萔
namespace {
	const Vector3f g_vEye(50.0f, 150.0f, -100.0f);
	const Vector3f g_vLook(0.0f, 0.0f, 0.0f);
	const Vector3f g_vUp(0.0f, 1.0f, 0.0f);
};
/*===========================================================================
  �R���X�g���N�^
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
	if (GetKeyPress(VK_UP))
	{

	}
	// ���_�ƒ����_���ړ��A����x�N�g������]
	XMMATRIX world = XMLoadFloat4x4(m_PlayerWorld);
	XMStoreFloat3(&m_vEye, XMVector3TransformCoord(
		XMLoadFloat3(&g_vEye), world));
	XMStoreFloat3(&m_vLook, XMVector3TransformCoord(
		XMLoadFloat3(&g_vLook), world));
	XMStoreFloat3(&m_vUp, XMVector3TransformNormal(
		XMLoadFloat3(&g_vUp), world));
	//-----------------------------------------------------------
	// ���_�ƒ����_���ړ��A����x�N�g������]
	//XMMATRIX world = XMLoadFloat4x4(&pPlayer->GetWorld());
	//m_vLook = *m_PlayerPos;
	//
	//Vector3f axisY = Vector3f(1, 0, 0);
	//Vector3f axisXZ = Vector3f(1, 0, 1);
	//Vector3f vLookAt = m_vLook * 3;
	//// ���ړ�
	//axisY = axisY.Cross(GetAxisZ());
	//
	//if (GetKeyPress(VK_LSHIFT)) {
	//	m_vEye = RotateQuaternion(axisY, m_vEye, -RAD(1));
	//	
	//}
	//if (GetKeyPress(VK_RSHIFT)) {
	//	m_vEye = RotateQuaternion(axisY, m_vEye, RAD(1));
	//}
	//// ---�c�ړ�---
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

	//XMVECTOR axis; //��]�p��
	////XZ����]�p�N�I�[�^�j�I���쐬
	//axis = XMVector3Normalize(XMVector3Cross(m_vEye, m_vUp));
	//XMVECTOR qt_xz = XMQuaternionRotationAxis(axis, 
	//	XMConvertToRadians(GetDragDistance(MOUSEBUTTON_L).y)); //XMConvertToRadians(�}�E�X�ړ���.y)
	////Y����]�p�N�I�[�^�j�I���쐬
	//axis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMVECTOR qt_y = XMQuaternionRotationAxis(axis, 
	//	XMConvertToRadians(GetDragDistance(MOUSEBUTTON_L).x));//XMConvertToRadians(�}�E�X�ړ���.x)
	////��]�̊|�����킹
	//XMVECTOR qt = XMQuaternionMultiply(qt_xz, qt_y);

	////�J������]
	//camera_pos = XMVector3Rotate(camera_pos, qt);
	//camera_pos += m_vLook;
	//m_vEye = camera_pos;
	////Up�x�N�g����]
	//camera_up = XMVector3Rotate(camera_up, qt);
	//m_vUp = camera_up;

	CCamera::Update();
}
