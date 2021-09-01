/*===========================================================================
  @file   Player.cpp
  @brief  プレイヤー管理
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "Player.h"
#include "Camera.h"
#include "light.h"
#include "FbxModel.h"
#include "Box.h"
#include "FileName.hpp"
#include "input.h"
#include "debugproc.h"
/*===========================================================================
  コンストラクタ
===========================================================================*/
PlayerClass::PlayerClass(Vector3f _pos, LightClass _light)
	:m_pModel(nullptr), m_Pos(_pos), m_Light(_light), m_Move(0, 0, 0),m_Rot(0,0,0), m_Size(0.5f, 0.5f, 0.5f),
	m_box(nullptr)
{
	m_bCanJump = false;
	m_bIsHit = false;
	XMStoreFloat4x4(&m_World, XMMatrixIdentity());
	Init();
}
/*===========================================================================
デストラクタ
===========================================================================*/
PlayerClass::~PlayerClass()
{
	Uninit();
}
/*===========================================================================
初期処理
===========================================================================*/
HRESULT PlayerClass::Init()
{
	HRESULT hr = S_OK;
	
	// FBXファイルの読み込み
	SAFE_DELETE(m_pModel);
	m_pModel = new CFbxModel();
	m_box = new BoxClass();
	hr = m_pModel->Init(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_BALL]);
	if (SUCCEEDED(hr)) {
		m_pModel->SetCamera(CCamera::Get()->GetEye());
		m_pModel->SetLight(m_Light);

		// 境界ボックス初期化
		m_vCenter = m_pModel->GetCenter();
		m_vBBox = m_pModel->GetBBox();
		m_vBBox *= m_Size;
		
		/*{
			TCHAR szMsg[256];
			_stprintf_s(szMsg, 256, _T("m_vBBox={%f, %f, %f}"),
				m_pModel->GetBBox().x, m_vBBox.y, m_vBBox.z);
			MessageBox(GetMainWnd(), szMsg, _T("確認"), MB_OK);
		}*/
	}
	hr = m_box->Init(&m_vBBox);
	if (FAILED(hr))
	{
		MessageBox(GetMainWnd(), "Boxエラー", _T("OK"), MB_OK);
	}
	m_vPosBBox = m_vCenter;
	return hr;
}
/*===========================================================================
終了処理
===========================================================================*/
void PlayerClass::Uninit()
{
	m_box->Uninit();
	SAFE_DELETE(m_box);
	SAFE_DELETE(m_pModel);
}
/*===========================================================================
更新処理
===========================================================================*/
void PlayerClass::Update()
{
	if (GetKeyPress(VK_L)) {
		m_Pos = RotateQuaternion(Vector3f(0, 1, 0), m_Pos, -RAD(2));

	}
	if (GetKeyPress(VK_J)) {
		m_Pos = RotateQuaternion(Vector3f(0, 1, 0), m_Pos, RAD(2));

	}
	
	if (GetKeyPress('W'))
	{
		m_Move.z += 1.0f;
		m_Pos += m_Move;
	}
	// 境界ボックス(AABB)の移動
	XMStoreFloat3(&m_vPosBBox,
		XMVector3TransformCoord(
			XMLoadFloat3(&m_vCenter),
			XMLoadFloat4x4(&m_World)));
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixTranslation(
		m_vPosBBox.x, m_vPosBBox.y, m_vPosBBox.z));
	m_box->SetWorld(matrix);

	PrintDebugProc("m_vCenter.x%f\n", m_vCenter.x);
	PrintDebugProc("m_vCenter.y%f\n", m_vCenter.y);
	PrintDebugProc("m_vCenter.z%f\n", m_vCenter.z);
	PrintDebugProc("m_vBBox.x%f\n", m_vBBox.x);
	PrintDebugProc("m_vBBox.z%f\n", m_vBBox.z);
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
	mtxRot = XMMatrixRotationRollPitchYaw(m_Rot.x, m_Rot.y, m_Rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);
	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);
	// ワールドマトリックスの設定
	XMStoreFloat4x4(&m_World, mtxWorld);

	CCamera* pCamera = CCamera::Get();
	// ---FBXファイル表示---
	SetBlendState(BS_NONE);			// アルファ処理しない
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eOpacityOnly);
	SetZWrite(false);
	SetBlendState(BS_ALPHABLEND);	// 半透明描画
	m_pModel->Render(m_World, pCamera->GetView(),
		pCamera->GetProj(), eTransparentOnly);
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
座標取得
===========================================================================*/
Vector3f PlayerClass::GetPos()const
{
	return m_Pos;
}
/*===========================================================================
ワールド変換取得
===========================================================================*/
XMFLOAT4X4& PlayerClass::GetWorld()
{
	return m_World;
}
/*===========================================================================
ジャンプできるか
===========================================================================*/
bool PlayerClass::canJump()
{
	return m_bCanJump;
}
