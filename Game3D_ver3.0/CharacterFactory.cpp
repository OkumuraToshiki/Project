/*===========================================================================
  @file   CharaFactory.h
  @brief  キャラクター生成
  @author 奥村俊紀
  @date   2021/09/21
===========================================================================*/
#include "CharacterFactory.h"
/*===========================================================================
*エンティティ作成用関数
*引数:(type)string型のクラス名
*戻り値:Entityの型
===========================================================================*/
BaseCharacter* CharaFactory::CreateEntity(CLASSNAME type, Vector3f pos )
{
	//探索
	typename  CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())return nullptr;
	//生成
	IBaseCreator* pCreator = (*it).second;
	return pCreator->Create(pos);
}
/*===========================================================================
*登録用関数
*引数:(type)string型のEntity名,(pCreator)作成者関数のポインタ
*戻り値:bool型
===========================================================================*/
bool CharaFactory::Register(CLASSNAME type, IBaseCreator* pCreator)
{
	//探索
	typename CreateMap::iterator it = m_CreateMap.find(type);
	if (it != m_CreateMap.end())
	{
		delete pCreator;
		return false;
	}
	//登録
	m_CreateMap[type] = pCreator;
	return true;
}