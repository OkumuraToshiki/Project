/*===========================================================================
  @file   Enemy.h
  @brief  エネミー管理
  @author 奥村俊紀
  @date   2021/09/01
===========================================================================*/
#include "Enemy.h"
#include "AssimpModel.h"
#include "Camera.h"
#include "FileName.hpp"
/*===========================================================================
  静的メンバ変数
===========================================================================*/
CAssimpModel* EnemyClass::m_pModel = nullptr;
Vector3f      EnemyClass::m_vCenter = Vector3f(0, 0, 0);
Vector3f      EnemyClass::m_vBBox = Vector3f(0, 0, 0);
int           EnemyClass::m_nRef = 0;
/*===========================================================================
  コンストラクタ
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
  デスストラクタ
===========================================================================*/
EnemyClass::~EnemyClass()
{
}
/*===========================================================================
  初期処理
===========================================================================*/
HRESULT EnemyClass::Init()
{
	HRESULT hr = S_OK;

	// FBXファイルの読み込み
	if (m_nRef == 0) {
		SAFE_DELETE(m_pModel);
		m_pModel = new CAssimpModel();
		if (!m_pModel->Load(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_ENEMY]))
		{
			hr = E_FAIL;
			MessageBoxA(GetMainWnd(), "モデルデータ読込エラー", "EnemyModel", MB_OK | MB_ICONEXCLAMATION);
		}
		else {
			m_pModel->SetCamera(CCamera::Get());
			m_pModel->SetLight(m_Light);

			// 境界ボックス初期化
			m_vCenter = m_pModel->GetCenter();
			m_vBBox = m_pModel->GetBBox();
			m_vBBox *= m_Size;
		}
	}
	//ボックス初期化
	m_box = new BoxClass();
	hr = m_box->Init(&m_vBBox);
	m_vPosBBox = m_vCenter;
	//参照カウンタ++
	m_nRef++;
	return hr;
}
/*===========================================================================
  終了処理
===========================================================================*/
void EnemyClass::Uninit()
{
	//--- 境界ボックスの解放---
	m_box->Uninit();
	SAFE_DELETE(m_box);
	//--- FBXモデルの解放---
	--m_nRef;
	if (m_nRef == 0) {
		SAFE_DELETE(m_pModel);
	}
}
/*===========================================================================
  更新処理
===========================================================================*/
void EnemyClass::Update()
{

	// 境界ボックス(AABB)の移動
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
  描画処理
===========================================================================*/
void EnemyClass::Draw()
{
	XMMATRIX mtxWorld, mtxSize, mtxRot, mtxTranslate;
	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	mtxSize = XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxSize);
	mtxRot = XMMatrixRotationRollPitchYaw(m_Rot.x, m_Rot.y, m_Rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	// ワールドマトリックスの設定
	XMStoreFloat4x4(&m_World, mtxWorld);
	m_pModel->SetCamera(CCamera::Get());
	m_pModel->SetLight(m_Light);
	// ---FBXファイル表示---
	m_pModel->Draw(GetDeviceContext(), m_World);
	//SetBlendState(BS_NONE);			// アルファ処理しない
	//SetZWrite(false);
	//SetBlendState(BS_ALPHABLEND);	// 半透明描画
	// eTransparentOnly);
	SetCullMode(CULLMODE_CCW);	// 背面カリング(裏を描かない)
	//---ボックス表示---
	if (m_bIsHit) {
		XMFLOAT4 vRed(1.0f, 0.0f, 0.0f, 0.5f);
		m_box->SetColor(&vRed);
	}
	else {
		XMFLOAT4 vGreen(0.0f, 1.0f, 0.0f, 0.5f);
		m_box->SetColor(&vGreen);
	}
	m_box->Draw(m_Light);	// 境界ボックス描画
	SetCullMode(CULLMODE_CW);	// 前面カリング(表を描かない)
	SetZWrite(true);
}
/*===========================================================================
クラス取得
===========================================================================*/
std::string EnemyClass::GetName()
{
	return "EnemyClass";
}
