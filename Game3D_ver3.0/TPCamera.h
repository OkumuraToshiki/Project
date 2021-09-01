/*===========================================================================
  @file   TPCamera.h
  @brief  ３人称視点カメラ
  @author HAL名古屋
  @date
===========================================================================*/
#ifndef _TPCAMERA_H_
#define _TPCAMERA_H_
#include "Camera.h"
class PlayerClass;
/*===========================================================================
   ３人称カメラクラス
===========================================================================*/
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