/*===========================================================================
  @file   TPCamera.h
  @brief  ‚RlÌ‹“_ƒJƒƒ‰
  @author HAL–¼ŒÃ‰®
  @date
===========================================================================*/
#ifndef _TPCAMERA_H_
#define _TPCAMERA_H_
#include "Camera.h"
class TPCamera:public CCamera
{
private:
public:
	TPCamera();
	~TPCamera();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
};
#endif // !_TPCAMERA_H_