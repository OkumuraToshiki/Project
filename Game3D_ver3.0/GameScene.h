/*===========================================================================
  @file   GameScene.h
  @brief  ÉQÅ[ÉÄÉVÅ[Éì
  @author âúë∫èrãI
  @date   2021/08/28
===========================================================================*/
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "BaseScene.h"
class TPCamera;
class PlayerClass;
class EnemyClass;
class LightClass;
/*===========================================================================
  GameSceneÉNÉâÉX
===========================================================================*/
class GameScene :public BaseScene
{
private:
	TPCamera*     m_pTPcamera;
	PlayerClass*  m_pPlayer;
	EnemyClass*   m_pEnemy;
	LightClass*    m_Light;
public:
	GameScene();
	~GameScene();
	void Init()override;
	void Uninit()override;
	BaseScene* Update()override;
	void Draw() const override;
	std::string GetSceneName();
};
#endif // !_GAMESCENE_H_