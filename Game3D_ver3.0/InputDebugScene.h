/*===========================================================================
  @file   InputCheckScene.h
  @brief  キー入力の確認
  @author 奥村俊紀
  @date   2021/09/09
===========================================================================*/
#ifndef _INPUTDEBUGSCENE_H_
#define _INPUTDEBUGSCENE_H_

#include "BaseScene.h"
/*===========================================================================
  InputDebugSceneクラス
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
