/*===========================================================================
  @file   Creator.h
  @brief  �I�u�W�F�N�g������
  @author �����r�I
  @date   2021/09/20
===========================================================================*/
#ifndef _CREATOR_H_
#define _CREATOR_H_
#include "BaseCharacter.h"
#include "VectorClass.h"

class IBaseCreator
{
public:
	virtual ~IBaseCreator() {};
	virtual BaseCharacter* Create(Vector3f pos)const = 0;
};
#endif // !_CREATOR_H
