/*===========================================================================
  @file   Camera.cpp
  @brief  カメラのベース
  @author HAL名古屋
  @date
  ->08/27 Draw()関数を改変
===========================================================================*/
#include "Camera.h"
#include "debugproc.h"
#include "input.h"

/*===========================================================================
   静的メンバ変数
===========================================================================*/
CCamera* CCamera::m_pCamera = nullptr;
Vector3f CCamera::m_vNowEye;	// 現在の視点
Vector3f CCamera::m_vNowLook;	// 現在の注視点
Vector3f CCamera::m_vNowUp;		// 現在の上方ベクトル
/*===========================================================================
   コンストラクタ
===========================================================================*/
CCamera::CCamera()
{
	m_vEye = Vector3f(0.0f, 100.0f, -100.0f);
	m_vLook = Vector3f(0.0f, 0.0f, 0.0f);
	m_vUp = Vector3f(0.0f, 1.0f, 0.0f);
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
	m_vNowEye = m_vEye;
	m_vNowLook = m_vLook;
	m_vNowUp = m_vUp;
	for (int i = 0; i < 6; ++i)
	{
		m_frusW[i] = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

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
	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;
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
	XMStoreFloat3(&m_vNowUp,
		XMVector3Normalize(XMLoadFloat3(&m_vNowUp)));
	// ビュー変換更新
	XMStoreFloat4x4(&m_mView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vNowEye),
		XMLoadFloat3(&m_vNowLook),
		XMLoadFloat3(&m_vNowUp)));
	// 射影変換更新
	XMStoreFloat4x4(&m_mProj,
		XMMatrixPerspectiveFovLH(m_fFOVY, m_fAspect,
			m_fNearZ, m_fFarZ));


	PrintDebugProc("ｼﾃﾝ:%f %f %f\n", m_vEye.x, m_vEye.y, m_vEye.z);
}/*===========================================================================
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
  
===========================================================================*/
XMMATRIX CCamera::GetCameraMatrix(Vector3f vLook, Vector3f vEye,Vector3f vUp)
{
	Vector3f forward, right, up;
	XMVECTOR vF, vR, vU;
	XMFLOAT4X4 world;
	XMMATRIX mW = XMMatrixIdentity();
	//カメラZ軸を求める
	forward.x = vLook.x - vEye.x;
	forward.y = vLook.y - vEye.y;
	forward.z = vLook.z - vEye.z;

	vF = XMLoadFloat3(&forward);
	vF = XMVector3Normalize(vF);
	XMStoreFloat3(&forward, vF);

	//カメラX軸を求める
	vU = XMLoadFloat3(&vUp);
	vR = XMVector3Cross(vU, vF);
	vR = XMVector3Normalize(vR);
	XMStoreFloat3(&right, vR);

	//カメラY軸を求める
	vU = XMVector3Cross(vF, vR);
	vU = XMVector3Normalize(vU);
	XMStoreFloat3(&up, vU);

	//カメラのワールド変換マトリックスを求める
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

	world._41 = vEye.x;
	world._42 = vEye.y;
	world._43 = vEye.z;
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
	XMMatrixInverse(&XMLoadFloat3(&vDev), mtxUnpro);
	//正規化
	XMVECTOR xmv = XMVector3Normalize(XMLoadFloat3(&vDev));
	XMStoreFloat3(&vDev, xmv);
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
	XMVECTOR xmv = XMVector3Normalize(XMLoadFloat3(&Dir));
	XMStoreFloat3(&Dir, xmv);
}
/*===========================================================================
  //方向ベクトル
===========================================================================*/
Vector3f CCamera::FPVector()
{

	XMVECTOR vVec = XMVectorSet(m_vNowLook.x - m_vNowEye.x,
		m_vNowLook.y - m_vNowEye.y,
		m_vNowLook.z - m_vNowEye.z, 0.0f);
	vVec = XMVector3Normalize(vVec);
	Vector3f vDir;
	XMStoreFloat3(&vDir, vVec);
	PrintDebugProc("ﾍﾞｸﾀｰ:%f,%f,%f\n", vDir.x, vDir.y, vDir.z);
	return vDir;
}