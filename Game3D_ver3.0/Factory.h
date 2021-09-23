/*===========================================================================
  @file   Factory.h
  @brief  オブジェクト生成
  @author 奥村俊紀
  @date   2021/09/20
===========================================================================*/
#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <map>
#include <string>

//エンティティタイプ
using CLASSNAME = std::string;
/*-------------------------------------------------
*作成関数用インターフェイス
-------------------------------------------------*/
template <class Base>
class ICreatorBase
{
public:
	virtual ~ICreatorBase() {};
	virtual Base* Create() const = 0;
};
/*-------------------------------------------------
*作成者クラス
-------------------------------------------------*/
template<class Product, class Base>
class CCreator :public ICreatorBase<Base>
{
public:
	//作成
	virtual Base* Create()const { return new Product(); }
};
/*-------------------------------------------------
*クラス名と作成者登録用
-------------------------------------------------*/
template <class Base>
class CFactory
{
private:
	using CreateMap = std::map<CLASSNAME, ICreatorBase<Base>* >;
	typename CreateMap m_CreateMap;
public:
	virtual ~CFactory() {};
	Base* CreateEntity(CLASSNAME type);
	bool Register(CLASSNAME type, ICreatorBase<Base>* pCreator);
};
/*-------------------------------------------------
*エンティティ作成用関数
*引数:(type)string型のクラス名
*戻り値:Entityの型
-------------------------------------------------*/
template<class Base>
Base* CFactory<Base>::CreateEntity(CLASSNAME type)
{
	//探索
	typename  CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())return nullptr;
	//生成
	ICreatorBase<Base>* pCreator = (*it).second;
	return pCreator->Create();
}
/*-------------------------------------------------
*登録用関数
*引数:(type)string型のEntity名,(pCreator)作成者関数のポインタ
*戻り値:bool型
-------------------------------------------------*/
template<class Base>
bool CFactory<Base>::Register(CLASSNAME type, ICreatorBase<Base>* pCreator)
{
	//探索
	typename CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())
	{
		delete pCreator;
		return false;
	}
	//登録
	m_CreateMap[type] = pCreator;
	return true;
}
#endif // !_FACTORY_H_