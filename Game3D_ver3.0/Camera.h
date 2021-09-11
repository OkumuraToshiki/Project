/*===========================================================================
  @file   Camera.h
  @brief  �J�����̃x�[�X
  @author HAL���É�
  @date
===========================================================================*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "VectorClass.h"
class CCamera
{
protected:
	Vector3f		m_vEye;		// ���_���W
	Vector3f		m_vLook;	// �����_���W
	Vector3f		m_vUp;		// ����x�N�g��
	XMFLOAT4X4		m_mView;	// �r���[�ϊ�
	XMFLOAT4X4		m_mProj;	// �ˉe�ϊ�
	float			m_fFOVY;	// ����p
	float			m_fAspect;	// �A�X�y�N�g��
	float			m_fNearZ;	// �O���N���b�v����
	float			m_fFarZ;	// ����N���b�v����
	static Vector3f	m_vNowEye;	// ���݂̎��_
	static Vector3f	m_vNowLook;	// ���݂̒����_
	static Vector3f	m_vNowUp;	// ���݂̏���x�N�g��
	XMFLOAT4        m_frusW[6]; //������(���[���h��ԗp)
private:
	static CCamera*	m_pCamera;	// ���ݗL���ȃJ����

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