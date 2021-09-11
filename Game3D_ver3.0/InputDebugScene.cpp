/*===========================================================================
  @file   InputCheckScene.cpp
  @brief  �L�[���͂̊m�F
  @author �����r�I
  @date   2021/09/09
===========================================================================*/
#include "InputDebugScene.h"
#include "input.h"
#include "debugproc.h"
class TitleScene;
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
InputDebugScene::InputDebugScene()
{
	
}
/*===========================================================================
  �f�X�g���N�^
===========================================================================*/
InputDebugScene::~InputDebugScene()
{
}
/*===========================================================================
  �X�V����
===========================================================================*/
BaseScene* InputDebugScene::Update()
{
	PrintDebugProc("---------------------------------------------------------------------\n");
	PrintDebugProc("PadNum   :%f\n", (float)GetJoyCount());
	PrintDebugProc("size     :%f\n", (float)GetJoyState(0)->dwSize);
	PrintDebugProc("flags    :%f\n", (float)GetJoyState(0)->dwFlags);
	PrintDebugProc("LStickX  :%f\n", (float)GetJoyX(0));//�E��65535�A����0
	PrintDebugProc("LStickY  :%f\n", (float)GetJoyState(0)->dwYpos);//�オ�O�A����65535
	PrintDebugProc("RStickX  :%f\n", (float)GetJoyState(0)->dwZpos);//�E��65535�A����0
	PrintDebugProc("RStickY  :%f\n", (float)GetJoyState(0)->dwRpos);//�オ�O�A����65535
	PrintDebugProc("R2       :%f\n", (float)GetJoyState(0)->dwUpos);//0�`65535
	PrintDebugProc("L2       :%f\n", (float)GetJoyState(0)->dwVpos);//0�`65535
	PrintDebugProc("buttonOn :%f\n", (float)GetJoyState(0)->dwButtons);//�{�^�������Ă��邩
	PrintDebugProc("ButtonNum:%f\n", (float)GetJoyState(0)->dwButtonNumber);//�ǂ̃{�^����
	PrintDebugProc("POV      :%f\n", (float)GetJoyState(0)->dwPOV);//�\���@��:0�A�E9000�A��18000�A��27000
	PrintDebugProc("reserved :%f\n", (float)GetJoyState(0)->dwReserved1);
	PrintDebugProc("%f\n", (float)GetJoyState(0)->dwReserved2);
	PrintDebugProc("---------------------------------------------------------------------\n");
	if (GetKeyTrigger(VK_RETURN))return makeScene<TitleScene>();
	return this;
}
/*===========================================================================
 �V�[������
===========================================================================*/
template<>
BaseScene *BaseScene::makeScene<InputDebugScene>() {
	return new InputDebugScene();
}