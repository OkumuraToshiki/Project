/*===========================================================================
  @file   ResultScene.cpp
  @brief  リザルトシーン
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "ResultScene.h"
#include "input.h"

class TitleScene;
/*===========================================================================
  コンストラクタ
===========================================================================*/
ResultScene::ResultScene()
{
}
/*===========================================================================
  デストラクタ
===========================================================================*/
ResultScene::~ResultScene()
{
}
/*===========================================================================
  初期処理
===========================================================================*/
void ResultScene::Init()
{
}
/*===========================================================================
  終了処理
===========================================================================*/
void ResultScene::Uninit()
{
}
/*===========================================================================
  更新処理
===========================================================================*/
BaseScene* ResultScene::Update()
{
	if (GetKeyTrigger(VK_RETURN))
	{
		return makeScene<TitleScene>();
	}
	return this;
}
/*===========================================================================
  描画処理
===========================================================================*/
void ResultScene::Draw() const
{
}
/*===========================================================================
  シーン名取得
===========================================================================*/
std::string ResultScene::GetSceneName()
{
	return "ResultScene";
}
/*===========================================================================
  リザルトシーン生成
===========================================================================*/
template<>
BaseScene *BaseScene::makeScene<ResultScene>()
{
	return new ResultScene();
}