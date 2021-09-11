/*===========================================================================
  @file   InputCheckScene.cpp
  @brief  キー入力の確認
  @author 奥村俊紀
  @date   2021/09/09
===========================================================================*/
#include "InputDebugScene.h"
#include "input.h"
#include "debugproc.h"
class TitleScene;
/*===========================================================================
  コンストラクタ
===========================================================================*/
InputDebugScene::InputDebugScene()
{
	
}
/*===========================================================================
  デストラクタ
===========================================================================*/
InputDebugScene::~InputDebugScene()
{
}
/*===========================================================================
  更新処理
===========================================================================*/
BaseScene* InputDebugScene::Update()
{
	PrintDebugProc("---------------------------------------------------------------------\n");
	PrintDebugProc("PadNum   :%f\n", (float)GetJoyCount());
	PrintDebugProc("size     :%f\n", (float)GetJoyState(0)->dwSize);
	PrintDebugProc("flags    :%f\n", (float)GetJoyState(0)->dwFlags);
	PrintDebugProc("LStickX  :%f\n", (float)GetJoyX(0));//右が65535、左が0
	PrintDebugProc("LStickY  :%f\n", (float)GetJoyState(0)->dwYpos);//上が０、下が65535
	PrintDebugProc("RStickX  :%f\n", (float)GetJoyState(0)->dwZpos);//右が65535、左が0
	PrintDebugProc("RStickY  :%f\n", (float)GetJoyState(0)->dwRpos);//上が０、下が65535
	PrintDebugProc("R2       :%f\n", (float)GetJoyState(0)->dwUpos);//0～65535
	PrintDebugProc("L2       :%f\n", (float)GetJoyState(0)->dwVpos);//0～65535
	PrintDebugProc("buttonOn :%f\n", (float)GetJoyState(0)->dwButtons);//ボタン押しているか
	PrintDebugProc("ButtonNum:%f\n", (float)GetJoyState(0)->dwButtonNumber);//どのボタンか
	PrintDebugProc("POV      :%f\n", (float)GetJoyState(0)->dwPOV);//十字　↑:0、右9000、↓18000、左27000
	PrintDebugProc("reserved :%f\n", (float)GetJoyState(0)->dwReserved1);
	PrintDebugProc("%f\n", (float)GetJoyState(0)->dwReserved2);
	PrintDebugProc("---------------------------------------------------------------------\n");
	if (GetKeyTrigger(VK_RETURN))return makeScene<TitleScene>();
	return this;
}
/*===========================================================================
 シーン生成
===========================================================================*/
template<>
BaseScene *BaseScene::makeScene<InputDebugScene>() {
	return new InputDebugScene();
}