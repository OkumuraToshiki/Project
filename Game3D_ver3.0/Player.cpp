/*===========================================================================
  @file   Player.cpp
  @brief  �v���C���[�Ǘ�
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#include "Player.h"
#include "Camera.h"
#include "light.h"
#include "AssimpModel.h"
#include "Box.h"
#include "FileName.hpp"
#include "input.h"
#include "debugproc.h"
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
PlayerClass::PlayerClass(Vector3f _pos, LightClass* _light)
	:m_pModel(nullptr), m_Pos(_pos), m_Light(_light), m_Move(0, 0, 0),m_Rot(0,0,0), m_Size(1.0f, 1.0f, 1.0f),
	m_box(nullptr)
{
	m_bCanJump = false;
	m_bIsHit = false;
	animTime = 0;
	XMStoreFloat4x4(&m_World, XMMatrixIdentity());
	Init();
}
/*===========================================================================
�f�X�g���N�^
===========================================================================*/
PlayerClass::~PlayerClass()
{
	Uninit();
}
/*===========================================================================
��������
===========================================================================*/
HRESULT PlayerClass::Init()
{
	HRESULT hr = S_OK;
	
	// FBX�t�@�C���̓ǂݍ���
	SAFE_DELETE(m_pModel);
	m_pModel = new CAssimpModel();
	m_box = new BoxClass();
	if (!m_pModel->Load(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_KNIGHT]))
	{
		hr = E_FAIL;
		MessageBoxA(GetMainWnd(), "���f���f�[�^�Ǎ��G���[", "PlayerModel", MB_OK | MB_ICONEXCLAMATION);
	}
	else {
		m_pModel->SetCamera(CCamera::Get());
		m_pModel->SetLight(m_Light);

		// ���E�{�b�N�X������
		m_vCenter = m_pModel->GetCenter();
		m_vBBox = m_pModel->GetBBox();
		m_vBBox *= m_Size;
		
		/*{
			TCHAR szMsg[256];
			_stprintf_s(szMsg, 256, _T("m_vBBox={%f, %f, %f}"),
				m_pModel->GetBBox().x, m_vBBox.y, m_vBBox.z);
			MessageBox(GetMainWnd(), szMsg, _T("�m�F"), MB_OK);
		}*/
	}
	hr = m_box->Init(&m_vBBox);
	if (FAILED(hr))
	{
		MessageBox(GetMainWnd(), "Box�G���[", _T("OK"), MB_OK);
	}
	m_vPosBBox = m_vCenter;
	return hr;
}
/*===========================================================================
�I������
===========================================================================*/
void PlayerClass::Uninit()
{
	m_box->Uninit();
	SAFE_DELETE(m_box);
	SAFE_DELETE(m_pModel);
}
/*===========================================================================
�X�V����
===========================================================================*/
void PlayerClass::Update()
{
	CCamera* pCamera = CCamera::Get();
	Vector2f cameraZ = Vector2f(pCamera->GetAxisZ().x, pCamera->GetAxisZ().z);
	PrintDebugProc("cameraZ:%f %f \n", cameraZ.x, cameraZ.y);
	if (GetKeyPress(VK_F1))m_Pos.y += 1.0f;
	if (GetKeyPress(VK_F2))m_Pos.y -= 1.0f;
	if (GetKeyPress(VK_L)) {
		m_Pos = RotateQuaternion(Vector3f(0, 1, 0), m_Pos, -RAD(2));

	}
	if (GetKeyPress(VK_J)) {
		m_Pos = RotateQuaternion(Vector3f(0, 1, 0), m_Pos, RAD(2));

	}
	Vector2f axisz = Vector2f(0, 1);
	float dir = cameraZ.Angle(axisz);
	PrintDebugProc("dotZ %f\n", dir);
	/*if (GetKeyPress('W'))
	{
		m_Move.x = 1.0f*sinf(dir);
		m_Move.z = 1.0f*cosf(dir);
		m_Pos += m_Move;
	}*/
	m_Move.x = InputPlayerMove().x;
	m_Move.z = InputPlayerMove().y;
	PrintDebugProc("MoveX %f\n", InputPlayerMove().x);
	PrintDebugProc("MoveY %f\n", InputPlayerMove().y);
	m_Pos += m_Move;
	// ���E�{�b�N�X(AABB)�̈ړ�
	XMStoreFloat3(&m_vPosBBox,
		XMVector3TransformCoord(
			XMLoadFloat3(&m_vCenter),
			XMLoadFloat4x4(&m_World)));
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixTranslation(
		m_vPosBBox.x, m_vPosBBox.y, m_vPosBBox.z));
	m_box->SetWorld(matrix);

	m_pModel->SetCamera(CCamera::Get());
	m_pModel->SetLight(m_Light);
	m_pModel->SetAnimIndex(0);
	if (GetKeyTrigger(VK_Q)) {
		animTime++;
	}
	m_pModel->SetAnimTime(animTime);
}
/*===========================================================================
�`�揈��
===========================================================================*/
void PlayerClass::Draw()
{
	XMMATRIX mtxWorld, mtxSize, mtxRot, mtxTranslate;
	// ���[���h�}�g���b�N�X�̏�����
	mtxWorld = XMMatrixIdentity();

	mtxSize = XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxSize);
	mtxRot = XMMatrixRotationRollPitchYaw(m_Rot.x, m_Rot.y, m_Rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	// ���[���h�}�g���b�N�X�̐ݒ�
	XMStoreFloat4x4(&m_World, mtxWorld);

	/*CCamera* pCamera = CCamera::Get();*/
	
	// ---FBX�t�@�C���\��---
	SetBlendState(BS_NONE);			// �A���t�@�������Ȃ�
	m_pModel->Draw(GetDeviceContext(), m_World, eOpacityOnly);
	SetZWrite(false);
	SetBlendState(BS_ALPHABLEND);	// �������`��
	m_pModel->Draw(GetDeviceContext(), m_World, eTransparentOnly);

	SetCullMode(CULLMODE_CCW);	// �w�ʃJ�����O(����`���Ȃ�)
	//---�{�b�N�X�\��---
	//if (m_bIsHit) {
	//	XMFLOAT4 vRed(1.0f, 0.0f, 0.0f, 0.5f);
	//	m_box->SetColor(&vRed);
	//}
	//else {
	//	XMFLOAT4 vGreen(0.0f, 1.0f, 0.0f, 0.5f);
	//	m_box->SetColor(&vGreen);
	//}
	//m_box->Draw(m_Light);	// ���E�{�b�N�X�`��
	SetCullMode(CULLMODE_CW);	// �O�ʃJ�����O(�\��`���Ȃ�)
	SetZWrite(true);
}
/*===========================================================================
���W�擾
===========================================================================*/
Vector3f& PlayerClass::GetPos()
{
	return m_Pos;
}
/*===========================================================================
���[���h�ϊ��擾
===========================================================================*/
XMFLOAT4X4& PlayerClass::GetWorld()
{
	return m_World;
}
/*===========================================================================
�W�����v�ł��邩
===========================================================================*/
bool PlayerClass::canJump()
{
	return m_bCanJump;
}
