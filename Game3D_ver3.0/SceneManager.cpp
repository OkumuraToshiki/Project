/*===========================================================================
  @file   SceneManager.cpp
  @brief  �V�[���J��
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#include "SceneManager.h"
#include "main.h"
#include "Fade.h"
class InitScene;
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
SceneManager::SceneManager(): m_pScene(makeScene<InitScene>()),m_pFade(new FadeClass())
{
}
/*===========================================================================
  �f�X�g���N�^
===========================================================================*/
SceneManager::~SceneManager()
{
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pScene);
}
/*===========================================================================
  �X�V
===========================================================================*/
BaseScene* SceneManager::Update()
{
	BaseScene* pCurrentScene = m_pScene->Update();
	m_pFade->Update();
	if (!m_pFade->isFade()) {
		if (pCurrentScene != m_pScene) {
			m_pFade->SetFadeout(10.0f);
			delete m_pScene;
			m_pScene = pCurrentScene;
			m_pFade->SetFadeIn(1.5f);
		}
	}
	return m_pScene;
}
/*===========================================================================
  �`��
===========================================================================*/
void SceneManager::Draw() const
{
	m_pScene->Draw();
	
	m_pFade->Draw();
}
