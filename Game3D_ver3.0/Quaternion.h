/*===========================================================================
  @file   Quaternion.h
  @brief  �N�I�[�^�j�I����`
  @author �����r�I
  @date   2021/08/30
===========================================================================*/
#ifndef _QUATERNION_H_
#define _QUATERNION_H_
#include "VectorClass.h"
//�N�I�[�^�j�I���\����

struct Quaternion
{
	float x, y, z, w;
};

void MultiplyQuaternion(Quaternion *pOut, Quaternion *pQ1, Quaternion *pQ2);
Quaternion MakeQuaternion(Vector3f Axis, float rad);
Vector3f RotateQuaternion(Vector3f axis, Vector3f pos, float radius);

#endif // !_QUATERNION_H_