#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
}

void GameScene::Uninit()
{
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
}
template<>
BaseScene *BaseScene::makeScene<GameScene>() {
	return new GameScene();