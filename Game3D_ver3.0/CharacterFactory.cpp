/*===========================================================================
  @file   CharacterFactory.cpp
  @brief  LN^[o^Aถฌ
  @author บrI
  @date   2021/09/21
===========================================================================*/
#include "CharacterFactory.h"
/*===========================================================================
*GeBeB์ฌpึ
*๘:(type)string^ฬNXผ
*฿่l:Entityฬ^
===========================================================================*/
BaseCharacter* CharaFactory::CreateEntity(CLASSNAME type, Vector3f pos )
{
	//T๕
	typename  CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())return nullptr;
	//ถฌ
	IBaseCreator* pCreator = (*it).second;
	return pCreator->Create(pos);
}
/*===========================================================================
*o^pึ
*๘:(type)string^ฬEntityผ,(pCreator)์ฌาึฬ|C^
*฿่l:bool^
===========================================================================*/
bool CharaFactory::Register(CLASSNAME type, IBaseCreator* pCreator)
{
	//T๕
	typename CreateMap::iterator it = m_CreateMap.find(type);
	if (it != m_CreateMap.end())
	{
		delete pCreator;
		return false;
	}
	//o^
	m_CreateMap[type] = pCreator;
	return true;
}