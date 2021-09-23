/*===========================================================================
  @file   Player.cpp
  @brief  プレイヤー管理
  @author 奥村俊紀
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
  コンストラクタ
===========================================================================*/
PlayerClass::PlayerClass(Vector3f _pos)
	:m_pModel(nullptr), m_Pos(_pos), m_Move(0, 0, 0),m_Rot(0,0,0), m_Size(1.0f, 1.0f, 1.0f),
	m_box(nullptr)
{
	m_bCanJump = false;
	m_bIsHit = false;
	animTime = 0;
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
	m_pModel = new CAssimpModel();
	m_box = new BoxClass();
	if (!m_pModel->Load(GetDevice(), GetDeviceContext(), pszModelPath[MODEL_KNIGHT]))
	{
		hr = E_FAIL;
		MessageBoxA(GetMainWnd(), "モデルデータ読込エラー", "PlayerClass", MB_OK | MB_ICONEXCLAMATION);
	}
	else {
		m_pModel->SetCamera(CCamera::Get());
		m_pModel->SetLight(LightClass::Get());

		// 境界ボックス初期化
		m_vCenter = m_pModel->GetCenter();
		m_vBBox = m_pModel->GetBBox();
		m_vBBox *= m_Size;
	}
	hr = m_box->Init(&m_vBBox);
	m_vPosBBox = m_vCenter;
#ifdef _DEBUG
	if (FAILED(hr))
	{
		MessageBox(GetMainWnd(), "Boxエラー", _T("OK"), MB_OK);
	}
#endif // _DEBUG
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
	// 境界ボックス(AABB)の移動
	XMStoreFloat3(&m_vPosBBox,
		XMVector3TransformCoord(
			XMLoadFloat3(&m_vCenter),
			XMLoadFloat4x4(&m_World)));
	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, XMMatrixTranslation(
		m_vPosBBox.x, m_vPosBBox.y, m_vPosBBox.z));
	m_box->SetWorld(matrix);

	m_pModel->SetAnimIndex(0);
	if (GetKeyTrigger(VK_Q)) {
		animTime++;
	}
	m_pModel->SetAnimTime(animTime);
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

	m_pModel->SetCamera(CCamera::Get());
	LightClass* pLight = LightClass::Get();
	m_pModel->SetLight(pLight);
	// ---FBXファイル表示---
	SetBlendState(BS_NONE);        // アルファ処理しない
	m_pModel->Draw(GetDeviceContext(), m_World, eOpacityOnly);
	SetZWrite(false);
	SetBlendState(BS_ALPHABLEND);  // 半透明描画
	m_pModel->Draw(GetDeviceContext(), m_World, eTransparentOnly);
#ifdef _DEBUG
	//---ボックス表示---
	SetCullMode(CULLMODE_CCW);	// 背面カリング(裏を描かない)
	if (m_bIsHit) {
		XMFLOAT4 vRed(1.0f, 0.0f, 0.0f, 0.5f);
		m_box->SetColor(&vRed);
	}
	else {
		XMFLOAT4 vGreen(0.0f, 1.0f, 0.0f, 0.5f);
		m_box->SetColor(&vGreen);
	}
	m_box->Draw(pLight);	// 境界ボックス描画
#endif // _DEBUG

	SetCullMode(CULLMODE_CW);	// 前面カリング(表を描かない)
	SetZWrite(true);
}
/*===========================================================================
クラス名取得
===========================================================================*/
std::string PlayerClass::GetName()
{
	return "PlayerClass";
}
/*===========================================================================
座標取得
===========================================================================*/
Vector3f& PlayerClass::GetPos()
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
BaseCharacter * PlayerClass::Create(Vector3f pos) const
{
	return new PlayerClass(pos);
}
/*===========================================================================
ジャンプできるか
===========================================================================*/
bool PlayerClass::canJump()
{
	return m_bCanJump;
}
