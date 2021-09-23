/*===========================================================================
  @file   Factory.h
  @brief  �I�u�W�F�N�g����
  @author �����r�I
  @date   2021/09/20
===========================================================================*/
#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <map>
#include <string>

//�G���e�B�e�B�^�C�v
using CLASSNAME = std::string;
/*-------------------------------------------------
*�쐬�֐��p�C���^�[�t�F�C�X
-------------------------------------------------*/
template <class Base>
class ICreatorBase
{
public:
	virtual ~ICreatorBase() {};
	virtual Base* Create() const = 0;
};
/*-------------------------------------------------
*�쐬�҃N���X
-------------------------------------------------*/
template<class Product, class Base>
class CCreator :public ICreatorBase<Base>
{
public:
	//�쐬
	virtual Base* Create()const { return new Product(); }
};
/*-------------------------------------------------
*�N���X���ƍ쐬�ғo�^�p
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
*�G���e�B�e�B�쐬�p�֐�
*����:(type)string�^�̃N���X��
*�߂�l:Entity�̌^
-------------------------------------------------*/
template<class Base>
Base* CFactory<Base>::CreateEntity(CLASSNAME type)
{
	//�T��
	typename  CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())return nullptr;
	//����
	ICreatorBase<Base>* pCreator = (*it).second;
	return pCreator->Create();
}
/*-------------------------------------------------
*�o�^�p�֐�
*����:(type)string�^��Entity��,(pCreator)�쐬�Ҋ֐��̃|�C���^
*�߂�l:bool�^
-------------------------------------------------*/
template<class Base>
bool CFactory<Base>::Register(CLASSNAME type, ICreatorBase<Base>* pCreator)
{
	//�T��
	typename CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())
	{
		delete pCreator;
		return false;
	}
	//�o�^
	m_CreateMap[type] = pCreator;
	return true;
}
#endif // !_FACTORY_H_