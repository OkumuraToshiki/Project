/*===========================================================================
  @file   GameScene.cpp
  @brief  ゲームシーン
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "GameScene.h"
#include "TPCamera.h"
#include "FieldMesh.h"
#include "Player.h"
#include "Enemy.h"
#include "light.h"
#include "input.h"
class ResultScene;
/*===========================================================================
  コンストラクタ
===========================================================================*/
GameScene::GameScene() :m_pLight(nullptr),m_pField(nullptr),m_pPlayer(nullptr),m_pEnemy(nullptr),m_pTPcamera(nullptr)
{
	m_pLight = new LightClass();
	m_pField = new FieldMeshClass();
	m_pPlayer = new PlayerClass(Vector3f(0, 0, 0), m_pLight);
	m_pEnemy = new EnemyClass(Vector3f(-50, 0, 200), m_pLight);
	m_pTPcamera = new TPCamera(&m_pPlayer->GetPos(),&m_pPlayer->GetWorld());
	CCamera::Set(m_pTPcamera);
}
/*===========================================================================
  デストラクタ
===========================================================================*/
GameScene::~GameScene()
{
	SAFE_DELETE(m_pField);
	SAFE_DELETE(m_pEnemy);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pLight);
	SAFE_DELETE(m_pTPcamera);
}
/*===========================================================================
  初期処理
===========================================================================*/
void GameScene::Init()
{
}
/*===========================================================================
  終了処理
===========================================================================*/
void GameScene::Uninit()
{
}
/*===========================================================================
  更新処理
===========================================================================*/
BaseScene* GameScene::Update()
{
	m_pField->Update();
	m_pPlayer->Update();
	m_pEnemy->Update();
	if (GetKeyTrigger(VK_RETURN))
	{
		return makeScene<ResultScene>();
	}
	return this;
}
/*===========================================================================
  描画処理
===========================================================================*/
void GameScene::Draw() const
{
	SetCullMode(CULLMODE_CCW);
	m_pField->Draw(m_pLight);
	Set3DMode();
	m_pEnemy->Draw();
	m_pPlayer->Draw();
	
}
std::string GameScene::GetSceneName()
{
	return "GameScene";
}
/*===========================================================================
  ゲームシーン生成
===========================================================================*/
template<>
BaseScene *BaseScene::makeScene<GameScene>() {
	return new GameScene();
}