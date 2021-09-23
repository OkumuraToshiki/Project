/*===========================================================================
  @file   CharaFactory.h
  @brief  キャラクター生成
  @author 奥村俊紀
  @date   2021/09/21
===========================================================================*/
#ifndef _CHARACTAR_FACTORY_
#define _CHARACTAR_FACTORY_
#include <map>
#include "Creator.h"
using CLASSNAME = std::string;

class CharaFactory
{
private:
	using CreateMap = std::map<CLASSNAME, IBaseCreator* >;
	typename CreateMap m_CreateMap;
public:
	virtual ~CharaFactory() {};
	BaseCharacter* CreateEntity(CLASSNAME type, Vector3f pos);
	bool Register(CLASSNAME type, IBaseCreator* pCreator);

};
#endif // !_CHARACTAR_FACTORY_
