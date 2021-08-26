/*===========================================================================
  Player.cpp
  プレイヤー管理
===========================================================================*/
#include "Player.h"
#include "Camera.h"
#include "light.h"
#include "FbxModel.h"
#include "Box.h"
#include "FileName.hpp"
#include "debugproc.h"
/*===========================================================================
  コンストラクタ
===========================================================================*/
PlayerClass::PlayerClass(Vector3f _pos, LightClass _light)
	: m_Pos(_pos.x, _pos.y, _pos.z), m_Light(_light), m_Move(0, 0, 0), m_Size(0.5f, 0.5f, 0.5f),
	m_vCenter(0, 0, 0), m_vBBox(0, 0, 0), m_vPosBBox(0, 0, 0)
{
	Init();
}
/*===========================================================================
デストラクタ
===========================================================================*/
PlayerClass::~PlayerClass()
{
}
/*===========================================================================
初期処理
===========================================================================*/
HRESULT PlayerClass::Init()
{
	HRESULT hr = S_OK;
	m_bCanJump = false;
	m_bIsHit = false;

	m_pModel = new CFbxModel();
	hr = m_pModel->Init(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_BALL]);
	if (SUCCEEDED(hr)) {
		m_pModel->SetCamera(CCamera::Get()->GetEye());
		m_pModel->SetLight(m_Light);

		// 境界ボックス初期化
		m_vCenter = m_pModel->GetCenter();
		m_vBBox = m_pModel->GetBBox();
	}
	hr = m_box.Init(&m_vBBox);
	m_vPosBBox = m_vCenter;
	return hr;
}
/*===========================================================================
終了処理
===========================================================================*/
void PlayerClass::Uninit()
{
	m_box.Uninit();
	SAFE_DELETE(m_pModel);
}
/*===========================================================================
更新処理
===========================================================================*/
void PlayerClass::Update()
{
	PrintDebugProc("ret%f", m_vBBox.x);
}
/*===========================================================================
描画処理
===========================================================================*/
void PlayerClass::Draw()
{
	XMMATRIX mtxWorld, mtxSize, mtxRot, mtxTranslate;
	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	mtxSize = XMMatrixScaling(m_Size.x, m_Size.y, m_Size.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxSize);
	/*mtxRot = XMMatrixRotationRollPitchYaw();
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);*/
	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	// ワールドマトリックスの設定
	XMStoreFloat4x4(&m_World, mtxWorld);

	CCamera* pCamera = CCamera::Get();
	// FBXファイル表示
	SetBlendState(BS_NONE);			// アルファ処理しない
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eOpacityOnly);
	SetZWrite(false);
	SetBlendState(BS_ALPHABLEND);	// 半透明描画
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eTransparentOnly);
	SetCullMode(CULLMODE_CCW);	// 背面カリング(裏を描かない)
	m_box.Draw(m_Light);	// 境界ボックス描画
	SetCullMode(CULLMODE_CW);	// 前面カリング(表を描かない)
	SetZWrite(true);
}
/*===========================================================================
ジャンプできるか
===========================================================================*/
bool PlayerClass::canJump()
{
	return m_bCanJump;
}
