/*===========================================================================
  @file   TPCamera.h
  @brief  RlÌ_J
  @author HAL¼Ã®
  @date
===========================================================================*/
#ifndef _TPCAMERA_H_
#define _TPCAMERA_H_
#include "Camera.h"
class PlayerClass;
class TPCamera:public CCamera
{
private:
	
public:
	TPCamera();
	~TPCamera();
	HRESULT Init();
	void Uninit();
	void Update(PlayerClass* pPlayer);
};
#endif // !_TPCAMERA_H_