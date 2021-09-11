/*===========================================================================
  @file   Camera.h
  @brief  カメラのベース
  @author HAL名古屋
  @date
===========================================================================*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "VectorClass.h"
class CCamera
{
protected:
	Vector3f		m_vEye;		// 視点座標
	Vector3f		m_vLook;	// 注視点座標
	Vector3f		m_vUp;		// 上方ベクトル
	XMFLOAT4X4		m_mView;	// ビュー変換
	XMFLOAT4X4		m_mProj;	// 射影変換
	float			m_fFOVY;	// 視野角
	float			m_fAspect;	// アスペクト比
	float			m_fNearZ;	// 前方クリップ距離
	float			m_fFarZ;	// 後方クリップ距離
	static Vector3f	m_vNowEye;	// 現在の視点
	static Vector3f	m_vNowLook;	// 現在の注視点
	static Vector3f	m_vNowUp;	// 現在の上方ベクトル
	XMFLOAT4        m_frusW[6]; //視錘台(ワールド空間用)
private:
	static CCamera*	m_pCamera;	// 現在有効なカメラ

public:
	CCamera();
	virtual ~CCamera();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();

	XMFLOAT4X4& GetView() { return m_mView; }
	XMFLOAT4X4& GetProj() { return m_mProj; }
	Vector3f& GetEye() { return m_vEye; }
	Vector3f& GetLook() { return m_vLook; }
	void SetLook(Vector3f vLook) { m_vLook = vLook; }
	static void Set(CCamera* pCamera)
	{
		m_pCamera = pCamera;
	}
	static CCamera* Get() { return m_pCamera; }
	int CollisionViewFrustum(Vector3f* pCenter, float fRadius);
	Vector3f GetAxisZ();
private:
	void SetFrustum();
	XMMATRIX GetMatrix();
	Vector3f UnProjection(const Vector3f& screenP);
	void GetScreenDirection(Vector3f& Start, Vector3f& Dir);
};

#endif // !_CAMERA_H_