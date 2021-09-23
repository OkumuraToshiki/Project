/*===========================================================================
  @file   CharacterFactory.cpp
  @brief  �L�����N�^�[�o�^�A����
  @author �����r�I
  @date   2021/09/21
===========================================================================*/
#include "CharacterFactory.h"
/*===========================================================================
*�G���e�B�e�B�쐬�p�֐�
*����:(type)string�^�̃N���X��
*�߂�l:Entity�̌^
===========================================================================*/
BaseCharacter* CharaFactory::CreateEntity(CLASSNAME type, Vector3f pos )
{
	//�T��
	typename  CreateMap::iterator it = m_CreateMap.find(type);
	if (it == m_CreateMap.end())return nullptr;
	//����
	IBaseCreator* pCreator = (*it).second;
	return pCreator->Create(pos);
}
/*===========================================================================
*�o�^�p�֐�
*����:(type)string�^��Entity��,(pCreator)�쐬�Ҋ֐��̃|�C���^
*�߂�l:bool�^
===========================================================================*/
bool CharaFactory::Register(CLASSNAME type, IBaseCreator* pCreator)
{
	//�T��
	typename CreateMap::iterator it = m_CreateMap.find(type);
	if (it != m_CreateMap.end())
	{
		delete pCreator;
		return false;
	}
	//�o�^
	m_CreateMap[type] = pCreator;
	return true;
}