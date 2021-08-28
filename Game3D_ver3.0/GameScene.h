/*===========================================================================
  @file   GameScene.h
  @brief  ÉQÅ[ÉÄÉVÅ[Éì
  @author âúë∫èrãI
  @date   2021/08/28
===========================================================================*/
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "BaseScene.h"
/*===========================================================================
  GameScene
===========================================================================*/
class GameScene :public BaseScene
{
private:

public:
	GameScene();
	~GameScene();
	void Init()override;
	void Uninit()override;
	BaseScene* Update()override;
	void Draw() const override;
};
#endif // !_GAMESCENE_H_