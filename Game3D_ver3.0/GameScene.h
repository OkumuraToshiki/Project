/*===========================================================================
  @file   GameScene.h
  @brief  �Q�[���V�[��
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "BaseScene.h"
class PlayerClass;
class LightClass;
/*===========================================================================
  GameScene
===========================================================================*/
class GameScene :public BaseScene
{
private:
	PlayerClass*  m_pPlayer;
	LightClass*    m_Light;
public:
	GameScene();
	~GameScene();
	void Init()override;
	void Uninit()override;
	BaseScene* Update()override;
	void Draw() const override;
};
#endif // !_GAMESCENE_H_