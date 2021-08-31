/*===========================================================================
  @file   TitleScene.cpp
  @brief  タイトルシーン
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "TitleScene.h"
#include "input.h"
class GameScene;

TitleScene::TitleScene()
{
	
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Uninit()
{
}

BaseScene* TitleScene::Update()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		return makeScene<GameScene>();
	}
	return this;
}

void TitleScene::Draw() const
{
}

std::string TitleScene::GetSceneName()
{
	return "TitleScene";
}

template<>
BaseScene *BaseScene::makeScene<TitleScene>() 
{
	return new TitleScene();
}