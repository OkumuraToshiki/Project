/*===========================================================================
  @file   TitleScene.cpp
  @brief  �^�C�g���V�[��
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#include "TitleScene.h"

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
	return this;
}

void TitleScene::Draw() const
{
}

template<>
BaseScene *BaseScene::makeScene<TitleScene>() 
{
	return new TitleScene();
}