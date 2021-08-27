#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "BaseScene.h"
class GameScene :public BaseScene
{
private:

public:
	GameScene();
	~GameScene();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif // !_GAMESCENE_H_