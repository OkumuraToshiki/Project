/*===========================================================================
  @file   CharacterManager.cpp
  @brief  キャラクター管理
  @author 奥村俊紀
  @date   2021/09/21
===========================================================================*/
#include <algorithm>
#include "CharacterManager.h"
#include "CharacterFactory.h"
#include "Player.h"
#include "Enemy.h"
/*===========================================================================
  コンストラクタ
===========================================================================*/
CharacterMgr::CharacterMgr():m_pFactory(new CharaFactory())
{
	m_pFactory->Register("PlayerClass", new PlayerClass);
	m_pFactory->Register("EnemyClass" , new EnemyClass );
	//m_List.emplace_back(m_pFactory->CreateEntity("PlayerClass", Vector3f(0, 0, 0)));
	m_List.emplace_back(m_pFactory->CreateEntity("EnemyClass", Vector3f(-50, 0, 100)));
}
/*===========================================================================
  デストラクタ
===========================================================================*/
CharacterMgr::~CharacterMgr()
{
	std::for_each(
		m_List.begin(),
		m_List.end(),
		[](BaseCharacter* pChara) {SAFE_DELETE(pChara); }
	);
	m_List.clear();
	SAFE_DELETE(m_pFactory);
}
/*===========================================================================
  更新
===========================================================================*/
void CharacterMgr::Update()
{
	std::for_each(
		m_List.begin(), 
		m_List.end(),
		[](BaseCharacter* pChara) {pChara->Update(); }
	);
}
/*===========================================================================
  描画
===========================================================================*/
void CharacterMgr::Draw()
{
	std::for_each(
		m_List.begin(),
		m_List.end(),
		[](BaseCharacter* pChara) {pChara->Draw(); }
	);
}
/*===========================================================================
  リストに追加
===========================================================================*/
void CharacterMgr::AddList(BaseCharacter* pChara)
{
	m_List.emplace_back(pChara);
}
