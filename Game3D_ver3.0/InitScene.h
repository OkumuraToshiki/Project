/*===========================================================================
  @file   InitScene.h
  @brief  �ŏ�(�^�C�g���̑O)�̃V�[��
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#ifndef _INITSCENE_H_
#define _INITSCENE_H_
#include "BaseScene.h"
class TitleScene;
class InitScene :public BaseScene
{
private:

public:
	InitScene(){}
	~InitScene() {}
	void Init()override {}
	void Uninit()override {}
	BaseScene* Update()override { return makeScene<TitleScene>(); }
	void Draw()const override {}
	std::string GetSceneName() { return "InitScene"; }
};
#endif // !_INITSCENE_H_

