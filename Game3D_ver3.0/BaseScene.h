/*===========================================================================
  @file   BaseScene.h
  @brief  各シーンの基本
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#ifndef _BASESCENE_H_
#define _BASESCENE_H_
class LightClass;
class BaseScene
{
private:
protected:
	BaseScene() {
	}
	template<typename T>
	BaseScene *makeScene();
public:
	BaseScene(const BaseScene &) = delete;
	BaseScene &operator=(const BaseScene &) = delete;

	virtual ~BaseScene() = default;
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual BaseScene* Update() = 0;
	virtual void Draw() const= 0;
protected:
	//LightClass* const m_Light;
};
#endif // !_BASESCENE_H_
