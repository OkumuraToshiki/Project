/*===========================================================================
  @file   BaseScene.h
  @brief  各シーンの基本
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#ifndef _BASESCENE_H_
#define _BASESCENE_H_
class BaseScene
{
private:
protected:
	template<typename T>
	BaseScene *makeScene();
public:
	virtual ~BaseScene() {}
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
};
#endif // !_BASESCENE_H_
