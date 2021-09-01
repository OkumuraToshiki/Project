/*===========================================================================
  @file   Enemy.h
  @brief  �G�l�~�[�Ǘ�
  @author �����r�I
  @date   2021/09/01
===========================================================================*/
#include "Enemy.h"
#include "Camera.h"
#include "FileName.hpp"
/*===========================================================================
  �ÓI�����o�ϐ�
===========================================================================*/
CFbxModel* EnemyClass::m_pModel = nullptr;
Vector3f   EnemyClass::m_vCenter = Vector3f(0, 0, 0);
Vector3f   EnemyClass::m_vBBox = Vector3f(0, 0, 0);
int        EnemyClass::m_nRef = 0;
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
EnemyClass::EnemyClass(Vector3f _pos, LightClass _light)
	: m_Pos(_pos), m_Move(0, 0, 0), m_Rot(0, 0, 0), m_Size(0.5f, 0.5f, 0.5f),
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
		m_pModel = new CFbxModel();
		hr = m_pModel->Init(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_BOX]);
		if (SUCCEEDED(hr)) {
			m_pModel->SetCamera(CCamera::Get()->GetEye());
			m_pModel->SetLight(m_Light);

			// ���E�{�b�N�X������
			m_vCenter = m_pModel->GetCenter();
			m_vBBox = m_pModel->GetBBox();
			m_vBBox *= m_Size;
		}
		else {
			return hr;
		}
	}
	m_box = new BoxClass();
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

	CCamera* pCamera = CCamera::Get();
	// ---FBX�t�@�C���\��---
	SetBlendState(BS_NONE);			// �A���t�@�������Ȃ�
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eOpacityOnly);
	SetZWrite(false);
	SetBlendState(BS_ALPHABLEND);	// �������`��
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eTransparentOnly);
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