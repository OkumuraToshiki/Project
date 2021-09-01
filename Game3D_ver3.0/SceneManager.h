/*===========================================================================
  @file   SceneManager.h
  @brief  ƒV[ƒ“‘JˆÚ
  @author ‰œ‘ºr‹I
  @date   2021/08/28
===========================================================================*/
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "BaseScene.h"
class FadeClass;
class SceneManager:public BaseScene
{
private:
	BaseScene* m_pScene;
	FadeClass* m_pFade;
public:
	SceneManager();
	SceneManager(const SceneManager &) = delete;
	SceneManager &operator=(const SceneManager &) = delete;
	~SceneManager();

	void Init() {}
	void Uninit() {}
	BaseScene* Update();
	void Draw() const;
	std::string GetSceneName() { return "SceneManager"; }
};
#endif // !_SCENEMANAGER_H_