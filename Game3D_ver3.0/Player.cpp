/*===========================================================================
  Player.cpp
  �v���C���[�Ǘ�
===========================================================================*/
#include "Player.h"
#include "Camera.h"
#include "light.h"
#include "FbxModel.h"
#include "Box.h"
#include "FileName.hpp"
#include "debugproc.h"
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
PlayerClass::PlayerClass(Vector3f _pos, LightClass _light)
	:m_pModel(nullptr), m_Pos(_pos.x, _pos.y, _pos.z), m_Light(_light), m_Move(0, 0, 0), m_Size(0.5f, 0.5f, 0.5f),
	m_vCenter(0, 0, 0), m_vBBox(0, 0, 0), m_vPosBBox(0, 0, 0)
{
	XMStoreFloat4x4(&m_World, XMMatrixIdentity());
	Init();
}
/*===========================================================================
�f�X�g���N�^
===========================================================================*/
PlayerClass::~PlayerClass()
{
}
/*===========================================================================
��������
===========================================================================*/
HRESULT PlayerClass::Init()
{
	HRESULT hr = S_OK;
	m_bCanJump = false;
	m_bIsHit = false;

	// FBX�t�@�C���̓ǂݍ���
	SAFE_DELETE(m_pModel);
	m_pModel = new CFbxModel();
	hr = m_pModel->Init(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_BALL]);
	if (SUCCEEDED(hr)) {
		m_pModel->SetCamera(CCamera::Get()->GetEye());
		m_pModel->SetLight(m_Light);

		// ���E�{�b�N�X������
		m_vCenter = m_pModel->GetCenter();
		m_vBBox = m_pModel->GetBBox();
		m_vBBox = m_vBBox * m_Size;
	}
	hr = m_box.Init(&m_vBBox);
	m_vPosBBox = m_vCenter;
	return hr;
}
/*===========================================================================
�I������
===========================================================================*/
void PlayerClass::Uninit()
{
	m_box.Uninit();
	SAFE_DELETE(m_pModel);
}
/*===========================================================================
�X�V����
===========================================================================*/
void PlayerClass::Update()
{
	// ���E�{�b�N�X(AABB)�̈ړ�
	XMStoreFloat3(&m_vPosBBox,
		XMVector3TransformCoord(
			XMLoadFloat3(&m_vCenter),
			XMLoadFloat4x4(&m_World)));
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixTranslation(
		m_vPosBBox.x, m_vPosBBox.y, m_vPosBBox.z));
	m_box.SetWorld(matrix);


	PrintDebugProc("ret%f\n", m_vBBox.z);
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
	/*mtxRot = XMMatrixRotationRollPitchYaw();
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);*/
	// �ړ��𔽉f
	mtxTranslate = XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	// ���[���h�}�g���b�N�X�̐ݒ�
	XMStoreFloat4x4(&m_World, mtxWorld);

	CCamera* pCamera = CCamera::Get();
	// FBX�t�@�C���\��
	SetBlendState(BS_NONE);			// �A���t�@�������Ȃ�
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eOpacityOnly);
	SetZWrite(false);
	SetBlendState(BS_ALPHABLEND);	// �������`��
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eTransparentOnly);
	SetCullMode(CULLMODE_CCW);	// �w�ʃJ�����O(����`���Ȃ�)
	if (m_bIsHit) {
		XMFLOAT4 vRed(1.0f, 0.0f, 0.0f, 0.5f);
		m_box.SetColor(&vRed);
	}
	else {
		XMFLOAT4 vGreen(0.0f, 1.0f, 0.0f, 0.5f);
		m_box.SetColor(&vGreen);
	}
	m_box.Draw(m_Light);	// ���E�{�b�N�X�`��
	SetCullMode(CULLMODE_CW);	// �O�ʃJ�����O(�\��`���Ȃ�)
	SetZWrite(true);
}
/*===========================================================================
�W�����v�ł��邩
===========================================================================*/
bool PlayerClass::canJump()
{
	return m_bCanJump;
}
