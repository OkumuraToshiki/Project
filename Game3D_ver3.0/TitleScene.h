/*===========================================================================
  @file   TitleScene.h
  @brief  タイトルシーン
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
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
