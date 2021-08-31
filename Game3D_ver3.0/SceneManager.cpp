/*===========================================================================
  @file   SceneManager.cpp
  @brief  シーン遷移
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "SceneManager.h"
#include "main.h"
#include "Fade.h"
#include "debugproc.h"
class InitScene;
/*===========================================================================
  コンストラクタ
===========================================================================*/
SceneManager::SceneManager() :m_pFade(new FadeClass()), m_pScene(makeScene<InitScene>())
{
}
/*===========================================================================
  デストラクタ
===========================================================================*/
SceneManager::~SceneManager()
{
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pScene);
}
/*===========================================================================
  更新
===========================================================================*/
BaseScene* SceneManager::Update()
{
	PrintDebugProc("%s\n", m_pScene->GetSceneName());
	BaseScene* pCurrentScene = m_pScene->Update();
	m_pFade->Update();

	if (pCurrentScene != m_pScene) {
		m_pFade->SetFadeout(1.0f);

		delete m_pScene;
		m_pScene = pCurrentScene;
		m_pFade->SetFadeIn(1.5f);
	}
	return m_pScene;
}
/*===========================================================================
  描画
===========================================================================*/
void SceneManager::Draw() const
{
	m_pScene->Draw();	
	m_pFade->Draw();
}
