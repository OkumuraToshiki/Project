/*===========================================================================
  @file   ResultScene.h
  @brief  リザルトシーン
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_
#include "BaseScene.h"
class ResultScene:public BaseScene
{
private:

public:
	ResultScene();
	~ResultScene();
	void Init()override;
	void Uninit()override;
	BaseScene* Update()override;
	void Draw() const override;
	std::string GetSceneName();
};

#endif // !_RESULTSCENE_H_
