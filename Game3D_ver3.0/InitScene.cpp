#include "InitScene.h"
template<>
BaseScene *BaseScene::makeScene<InitScene>()
{
	return new InitScene();
}