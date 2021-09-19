/*===========================================================================
  @file   Enemy.h
  @brief  �G�l�~�[�Ǘ�
  @author �����r�I
  @date   2021/09/01
===========================================================================*/
#include "Enemy.h"
#include "AssimpModel.h"
#include "Camera.h"
#include "FileName.hpp"
/*===========================================================================
  �ÓI�����o�ϐ�
===========================================================================*/
CAssimpModel* EnemyClass::m_pModel = nullptr;
Vector3f      EnemyClass::m_vCenter = Vector3f(0, 0, 0);
Vector3f      EnemyClass::m_vBBox = Vector3f(0, 0, 0);
int           EnemyClass::m_nRef = 0;
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
EnemyClass::EnemyClass(Vector3f _pos, LightClass* _light)
	: m_Pos(_pos), m_Move(0, 0, 0), m_Rot(0, 0, 0), m_Size(1.0f, 1.0f, 1.0f),
	 m_Light(_light), m_box(nullptr)
{
	m_bCanJump = false;
	m_bIsHit = false;
	XMStoreFloat4x4(&m_World, XMMatrixIdentity());
	Init();
}
/*===========================================================================
  �f�X�X�g���N�^
===========================================================================*/
EnemyClass::~EnemyClass()
{
}
/*===========================================================================
  ��������
===========================================================================*/
HRESULT EnemyClass::Init()
{
	HRESULT hr = S_OK;

	// FBX�t�@�C���̓ǂݍ���
	if (m_nRef == 0) {
		SAFE_DELETE(m_pModel);
		m_pModel = new CAssimpModel();
		if (!m_pModel->Load(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_ENEMY]))
		{
			hr = E_FAIL;
			MessageBoxA(GetMainWnd(), "���f���f�[�^�Ǎ��G���[", "EnemyModel", MB_OK | MB_ICONEXCLAMATION);
		}
		else {
			m_pModel->SetCamera(CCamera::Get());
			m_pModel->SetLight(m_Light);

			// ���E�{�b�N�X������
			m_vCenter = m_pModel->GetCenter();
			m_vBBox = m_pModel->GetBBox();
			m_vBBox *= m_Size;
		}
	}
	//�{�b�N�X������
	m_box = new BoxClass();
	hr = m_box->Init(&m_vBBox);
	m_vPosBBox = m_vCenter;
	//�Q�ƃJ�E���^++
	m_nRef++;
	return hr;
}
/*===========================================================================
  �I������
===========================================================================*/
void EnemyClass::Uninit()
{
	//--- ���E�{�b�N�X�̉��---
	m_box->Uninit();
	SAFE_DELETE(m_box);
	//--- FBX���f���̉��---
	--m_nRef;
	if (m_nRef == 0) {
		SAFE_DELETE(m_pModel);
	}
}
/*===========================================================================
  �X�V����
===========================================================================*/
void EnemyClass::Update()
{

	// ���E�{�b�N�X(AABB)�̈ړ�
	XMStoreFloat3(&m_vPosBBox,
		XMVector3TransformCoord(
			XMLoadFloat3(&m_vCenter),
			XMLoadFloat4x4(&m_World)));
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixTranslation(
		m_vPosBBox.x, m_vPosBBox.y, m_vPosBBox.z));
	m_box->SetWorld(matrix);
}
/*===========================================================================
  �`�揈��
===========================================================================*/
void EnemyClass::Draw()
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
	m_pModel->SetCamera(CCamera::Get());
	m_pModel->SetLight(m_Light);
	// ---FBX�t�@�C���\��---
	m_pModel->Draw(GetDeviceContext(), m_World);
	//SetBlendState(BS_NONE);			// �A���t�@�������Ȃ�
	//SetZWrite(false);
	//SetBlendState(BS_ALPHABLEND);	// �������`��
	// eTransparentOnly);
	SetCullMode(CULLMODE_CCW);	// �w�ʃJ�����O(����`���Ȃ�)
	//---�{�b�N�X�\��---
	if (m_bIsHit) {
		XMFLOAT4 vRed(1.0f, 0.0f, 0.0f, 0.5f);
		m_box->SetColor(&vRed);
	}
	else {
		XMFLOAT4 vGreen(0.0f, 1.0f, 0.0f, 0.5f);
		m_box->SetColor(&vGreen);
	}
	m_box->Draw(m_Light);	// ���E�{�b�N�X�`��
	SetCullMode(CULLMODE_CW);	// �O�ʃJ�����O(�\��`���Ȃ�)
	SetZWrite(true);
}
/*===========================================================================
�N���X�擾
===========================================================================*/
std::string EnemyClass::GetName()
{
	return "EnemyClass";
}
