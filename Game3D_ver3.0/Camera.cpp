/*===========================================================================
  @file   Camera.cpp
  @brief  カメラのベース
  @author HAL名古屋
  @date   08/27->09/23視錘台見直し
===========================================================================*/
#include "Camera.h"
#include "debugproc.h"
#include "input.h"

/*===========================================================================
   静的メンバ変数
===========================================================================*/
CCamera* CCamera::m_pCamera = nullptr;
Vector3f CCamera::m_vNowEye = Vector3f(0, 0, 0);    // 現在の視点
Vector3f CCamera::m_vNowLook = Vector3f(0, 0, 0);   // 現在の注視点
Vector3f CCamera::m_vNowUp = Vector3f(0, 0, 0);     // 現在の上方ベクトル
/*===========================================================================
   コンストラクタ
===========================================================================*/
CCamera::CCamera()
{
	Init();

	Update();
}
/*===========================================================================
   デストラクタ
===========================================================================*/
CCamera::~CCamera()
{
}
/*===========================================================================
   初期化
===========================================================================*/
HRESULT CCamera::Init()
{
	HRESULT hr = S_OK;
	m_vEye = Vector3f(0.0f, 100.0f, -100.0f);
	m_vLook = Vector3f(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3f(0.0f, 1.0f, 0.0f);
	m_fViewAngle = 45.0f;
	m_fFovy = XMConvertToRadians(m_fViewAngle);
	m_fAspect = (float)(SCREEN_WIDTH / SCREEN_HEIGHT);
	m_fNearZ = 1.0f;
	m_fFarZ = 1000.0f;
	m_vNowEye = m_vEye;
	m_vNowLook = m_vLook;
	m_vNowUp = m_vUp;
	for (int i = 0; i < 6; ++i)
	{
		m_frusW[i] = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	
	Update();
	return hr;
}

/*===========================================================================
   終了
===========================================================================*/
void CCamera::Uninit()
{
	
}

/*===========================================================================
   更新
===========================================================================*/
void CCamera::Update()
{
	// 視点、注視点、上方ベクトルを近づける
	m_vNowEye.x = m_vNowEye.x * 0.8f + m_vEye.x * 0.2f;
	m_vNowEye.y = m_vNowEye.y * 0.8f + m_vEye.y * 0.2f;
	m_vNowEye.z = m_vNowEye.z * 0.8f + m_vEye.z * 0.2f;
	m_vNowLook.x = m_vNowLook.x * 0.8f + m_vLook.x * 0.2f;
	m_vNowLook.y = m_vNowLook.y * 0.8f + m_vLook.y * 0.2f;
	m_vNowLook.z = m_vNowLook.z * 0.8f + m_vLook.z * 0.2f;
	m_vNowUp.x = m_vNowUp.x * 0.8f + m_vUp.x * 0.2f;
	m_vNowUp.y = m_vNowUp.y * 0.8f + m_vUp.y * 0.2f;
	m_vNowUp.z = m_vNowUp.z * 0.8f + m_vUp.z * 0.2f;
	//正規化
	m_vNowUp.Normalize();
	
	// ビュー変換更新
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(
		XMVECTOR(m_vNowEye),
		XMVECTOR(m_vNowLook),
		XMVECTOR(m_vNowUp)));
	// 射影変換更新
	XMStoreFloat4x4(&m_mProj,
		XMMatrixPerspectiveFovLH(m_fFovy, m_fAspect,
			m_fNearZ, m_fFarZ));

	//視錘台設定
	SetFrustum();

	PrintDebugProc("Eye:%f %f %f\n", m_vEye.x, m_vEye.y, m_vEye.z);
	PrintDebugProc("Look:%f %f %f\n", m_vLook.x, m_vLook.y, m_vLook.z);
	PrintDebugProc("Up:%f %f %f\n", m_vUp.x, m_vUp.y, m_vUp.z);
}
/*===========================================================================
    //視錘台との交差判定  (境界球使用)
    //引数　pCenter->モデルの中心、fRadius->モデルの半径
	//戻り値 0非表示 1部分表示 2表示
===========================================================================*/
int CCamera::CollisionViewFrustum(Vector3f* pCenter, float fRadius)
{
	bool bHit = false;
	XMVECTOR frusw, center, dot;

	float fDot;
	center = XMLoadFloat3(pCenter);
	for (int i = 0; i < 6; ++i)
	{
		frusw = XMLoadFloat4(&m_frusW[i]);
		dot = XMPlaneDotCoord(frusw, center);
		XMStoreFloat(&fDot, dot);
		if (fDot < -fRadius)return 0;//完全に外
		if (fDot <= fRadius)bHit = true;
	}
	if (bHit) return-1;//面を跨ぐ
	return 1;//完全に内側
}
/*===========================================================================
   //カメラのZ軸を求める
===========================================================================*/
Vector3f CCamera::GetAxisZ()
{
	Vector3f forward;
	//カメラZ軸を求める
	forward = m_vLook - m_vEye;
	forward.Normalize();
	return forward;
}
/*===========================================================================
   視錘台設定
===========================================================================*/
void CCamera::SetFrustum()
{
	//視錘台の上下左右の法線ベクトルを求める
	XMFLOAT4 m_frus[6];//視錘台 0上 1下 2左 3右 4前 5後
	float fTan = tanf(XMConvertToRadians(m_fViewAngle*0.5f));
	//上下
	m_frus[0] = XMFLOAT4(0, -1.0f, fTan, 0.0f);
	m_frus[1] = XMFLOAT4(0.0f, 1.0f, fTan, 0.0f);
	//左右
	fTan *= m_fAspect;//アスペクト比をかける
	m_frus[2] = XMFLOAT4(1.0f, 0.0f, fTan, 0.0f);
	m_frus[3] = XMFLOAT4(-1.0f, 0.0f, fTan, 0.0f);
	//前後
	m_frus[4] = XMFLOAT4(0.0f, 0.0f, 1.0, -m_fNearZ);
	m_frus[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, m_fFarZ);

	//正規化
	for (int i = 0; i < 4; ++i)
	{
		XMStoreFloat4(&m_frus[i],
			XMPlaneNormalize(XMLoadFloat4(&m_frus[i])));
	}
	//カメラの移動に伴い、視錘台をワールド変換
	XMMATRIX mW;
	mW = GetMatrix();
	//平面をワールド空間に配置
	mW = XMMatrixInverse(nullptr, mW);
	mW = XMMatrixTranspose(mW);
	for (int i = 0; i < 6; ++i)
	{
		XMStoreFloat4(&m_frusW[i],
			XMPlaneTransform(//※ワールドマトリックスは、逆行列の転置行列を渡す
				XMLoadFloat4(&m_frus[i]), mW));
	}
}
/*===========================================================================
  カメラのワールド変換行列を求める
===========================================================================*/
XMMATRIX CCamera::GetMatrix()
{
	Vector3f forward, right, up;
	XMFLOAT4X4 world;
	XMMATRIX mW = XMMatrixIdentity();
	//カメラZ軸を求める
	forward = GetAxisZ();
	//カメラX軸を求める
	right = m_vUp.Cross(forward);
	right.Normalize();

	//カメラY軸を求める
	up = forward.Cross(right);
	up.Normalize();

	//マトリックスを求める
	world._11 = right.x;
	world._12 = right.y;
	world._13 = right.z;
	world._14 = 0.0f;

	world._21 = up.x;
	world._22 = up.y;
	world._23 = up.z;
	world._24 = 0.0f;

	world._31 = forward.x;
	world._32 = forward.y;
	world._33 = forward.z;
	world._34 = 0.0f;

	world._41 = m_vEye.x;
	world._42 = m_vEye.y;
	world._43 = m_vEye.z;
	world._44 = 1.0f;

	mW = XMLoadFloat4x4(&world);
	return mW;
}

/*===========================================================================
   //逆射影行列計算
===========================================================================*/
Vector3f CCamera::UnProjection(const Vector3f& screenP)
{
	Vector3f vDev = Vector3f(screenP.x, screenP.y, screenP.z);
	vDev.x /= SCREEN_WIDTH * 0.5f;
	vDev.y /= SCREEN_HEIGHT * 0.5f;

	//逆射影
	XMMATRIX   mtxUnpro;
	//XMFLOAT4X4 unproject;
	mtxUnpro = XMLoadFloat4x4(&m_mView) * XMLoadFloat4x4(&m_mProj);
	XMMatrixInverse(&XMVECTOR(vDev), mtxUnpro);
	//正規化
	vDev.Normalize();
	return vDev;
}
/*===========================================================================
   スクリーンから向き
===========================================================================*/
void CCamera::GetScreenDirection(Vector3f& Start, Vector3f& Dir)
{
	XMFLOAT2 vPos = GetMousePos();
	Vector3f vS = Vector3f(vPos.x, vPos.y, 0.0f);
	Start = UnProjection(vS);

	vS.z = 0.9f;
	Vector3f vE = UnProjection(vS);

	//方向ベクトル
	Dir.x = vE.x - Start.x;
	Dir.y = vE.y - Start.y;
	Dir.z = vE.z - Start.z;
	//正規化
	Dir.Normalize();
}
