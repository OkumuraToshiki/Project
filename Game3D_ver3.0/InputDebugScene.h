/*===========================================================================
  @file   InputCheckScene.h
  @brief  �L�[���͂̊m�F
  @author �����r�I
  @date   2021/09/09
===========================================================================*/
#ifndef _INPUTDEBUGSCENE_H_
#define _INPUTDEBUGSCENE_H_

#include "BaseScene.h"
/*===========================================================================
  InputDebugScene�N���X
===========================================================================*/
class InputDebugScene :public BaseScene
{
private:
	
public:
	InputDebugScene();
	~InputDebugScene();
	void Init()override{}
	void Uninit()override{}
	BaseScene* Update()override;
	void Draw() const override{}
	std::string GetSceneName() { return "InputDebugScene"; }
};
#endif // !_INPUTCHECKSCENE_H_
