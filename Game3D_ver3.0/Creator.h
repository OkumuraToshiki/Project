/*===========================================================================
  @file   Creator.h
  @brief  オブジェクト生成者
  @author 奥村俊紀
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
