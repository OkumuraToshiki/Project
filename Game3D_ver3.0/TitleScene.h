#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_
#include "BaseScene.h"
class TitleScene:public BaseScene
{
private:

public:
	TitleScene();
	~TitleScene();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
#endif // !_TITLESCENE_H_
