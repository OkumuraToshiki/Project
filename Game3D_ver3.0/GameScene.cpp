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
	m_Light = new LightClass();
	m_pPlayer = new PlayerClass(Vector3f(0, 0, 0), m_Light);
	m_pEnemy = new EnemyClass(Vector3f(-50, 0, 200), m_Light);
	m_pTPcamera = new TPCamera(&m_pPlayer->GetPos(),&m_pPlayer->GetWorld());
	CCamera::Set(m_pTPcamera);
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
	Set3DMode();
	//m_pEnemy->Draw();
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