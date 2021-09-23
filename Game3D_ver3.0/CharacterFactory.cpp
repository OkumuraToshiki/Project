/*===========================================================================
  @file   CharacterFactory.cpp
  @brief  ƒLƒƒƒ‰ƒNƒ^[“o˜^A¶¬
  @author ‰œ‘ºr‹I
  @date   2021/09/21
===========================================================================*/
#include "CharacterFactory.h"
/*===========================================================================
*ƒGƒ“ƒeƒBƒeƒBì¬—pŠÖ”
*ˆø”:(type)stringŒ^‚ÌƒNƒ‰ƒX–¼
*–ß‚è’l:Entity‚ÌŒ^
===========================================================================*/
BaseCharacter* CharaFactory::CreateEntity(CLASSNAME type, Vector3f pos )
{
	//’Tõ
	typename  CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())return nullptr;
	//¶¬
	IBaseCreator* pCreator = (*it).second;
	return pCreator->Create(pos);
}
/*===========================================================================
*“o˜^—pŠÖ”
*ˆø”:(type)stringŒ^‚ÌEntity–¼,(pCreator)ì¬ÒŠÖ”‚Ìƒ|ƒCƒ“ƒ^
*–ß‚è’l:boolŒ^
===========================================================================*/
bool CharaFactory::Register(CLASSNAME type, IBaseCreator* pCreator)
{
	//’Tõ
	typename CreateMap::iterator it = m_CreateMap.find(type);
	if (it != m_CreateMap.end())
	{
		delete pCreator;
		return false;
	}
	//“o˜^
	m_CreateMap[type] = pCreator;
	return true;
}