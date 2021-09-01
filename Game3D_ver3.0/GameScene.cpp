/*===========================================================================
  @file   GameScene.cpp
  @brief  �Q�[���V�[��
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#include "GameScene.h"
#include "TPCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "light.h"
#include "input.h"
class ResultScene;
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
GameScene::GameScene()
{
	m_pTPcamera = new TPCamera();
	CCamera::Set(m_pTPcamera);
	m_Light = new LightClass();
	m_Light->SetDirection(Vector3f(0.5f, -1.0f, 0.5f));
	m_Light->SetDiffuse(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_Light->SetAmbient(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	m_Light->SetSpecular(Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
	m_pPlayer = new PlayerClass(Vector3f(0, 0, 100), *m_Light);
	m_pEnemy = new EnemyClass(Vector3f(-50, 0, 200), *m_Light);
}
/*===========================================================================
  �f�X�g���N�^
===========================================================================*/
GameScene::~GameScene()
{
	SAFE_DELETE(m_pEnemy);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pTPcamera);
}
/*===========================================================================
  ��������
===========================================================================*/
void GameScene::Init()
{
}
/*===========================================================================
  �I������
===========================================================================*/
void GameScene::Uninit()
{
}
/*===========================================================================
  �X�V����
===========================================================================*/
BaseScene* GameScene::Update()
{
	m_pTPcamera->Update(m_pPlayer);
	m_pPlayer->Update();
	m_pEnemy->Update();
	if (GetKeyTrigger(VK_RETURN))
	{
		return makeScene<ResultScene>();
	}
	return this;
}
/*===========================================================================
  �`�揈��
===========================================================================*/
void GameScene::Draw() const
{
	m_pEnemy->Draw();
	m_pPlayer->Draw();
	
}
std::string GameScene::GetSceneName()
{
	return "GameScene";
}
/*===========================================================================
  �Q�[���V�[������
===========================================================================*/
template<>
BaseScene *BaseScene::makeScene<GameScene>() {
	return new GameScene();
}