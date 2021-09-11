/*===========================================================================
  @file   TPCamera.h
  @brief  ３人称視点カメラ
  @author HAL名古屋
  @date
===========================================================================*/
#ifndef _TPCAMERA_H_
#define _TPCAMERA_H_
#include "Camera.h"
#include "VectorClass.h"
/*===========================================================================
   ３人称カメラクラス
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