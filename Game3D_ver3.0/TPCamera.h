/*===========================================================================
  @file   TPCamera.h
  @brief  �R�l�̎��_�J����
  @author HAL���É�
  @date
===========================================================================*/
#ifndef _TPCAMERA_H_
#define _TPCAMERA_H_
#include "Camera.h"
#include "VectorClass.h"
/*===========================================================================
   �R�l�̃J�����N���X
===========================================================================*/
class TPCamera:public CCamera
{
private:
	Vector3f*  m_PlayerPos;
	XMFLOAT4X4* m_PlayerWorld;
public:
	TPCamera();
	TPCamera(Vector3f* pos,XMFLOAT4X4* world);
	~TPCamera();
	HRESULT Init();
	void Uninit();
	void Update();
};
#endif // !_TPCAMERA_H_