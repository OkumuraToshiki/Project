/*===========================================================================
  @file   InitScene.h
  @brief  最初(タイトルの前)のシーン
  @author 奥村俊紀
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

