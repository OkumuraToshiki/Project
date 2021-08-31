/*===========================================================================
  @file   Quaternion.h
  @brief  �N�I�[�^�j�I����`
  @author �����r�I
  @date   2021/08/30
===========================================================================*/
#include "Quaternion.h"
/*===========================================================================
 * @brief   �N�H�[�^�j�I���̊|���Z
 * @param   pOut   �v�Z����
 * @param   pQ1    �v�Z�̍��̍�
 * @param   pQ2	   �v�Z�̉E�̍�
 * @return  ����
===========================================================================*/
void MultiplyQuaternion(Quaternion* pOut, Quaternion* pQ1, Quaternion* pQ2)
{
	pOut->w = pQ1->w * pQ2->w - pQ1->x * pQ2->x - pQ1->y * pQ2->y - pQ1->z * pQ2->z;
	pOut->x = pQ1->w * pQ2->x + pQ2->w * pQ1->x + pQ1->y * pQ2->z - pQ1->z * pQ2->y;
	pOut->y = pQ1->w * pQ2->y + pQ2->w * pQ1->y + pQ1->z * pQ2->x - pQ1->x * pQ2->z;
	pOut->z = pQ1->w * pQ2->z + pQ2->w * pQ1->z + pQ1->x * pQ2->y - pQ1->y * pQ2->x;
}
/*===========================================================================
 * @brief   �N�H�[�^�j�I���쐬
 * @param   axis    ��]�����鎲
 * @param   radian  ��]������p�x(���W�A��)
 * @return  �쐬�����N�H�[�^�j�I��
===========================================================================*/
Quaternion MakeQuaternion(Vector3f axis, float rad)
{
	Quaternion quaternion;      // �쐬����N�H�[�^�j�I��
	float halfSin, halfCos;      // �������p�x�̔�����sin,cos

	quaternion = { 0,0,0,0 };
	// ��]���̒�����0�̏ꍇ
	if(axis.Length() <= 0.0f)return quaternion;
	//���K��
	axis.Normalize();

	halfSin = sinf(rad * 0.5f);
	halfCos = cosf(rad * 0.5f);

	quaternion.w = halfCos;
	quaternion.x = axis.x * halfSin;
	quaternion.y = axis.y * halfSin;
	quaternion.z = axis.z * halfSin;

	return quaternion;
}
/*===========================================================================
 * @brief   �N�H�[�^�j�I���ɂ���]
 * @param   axis    ��]����������
 * @param   pos     ��]������I�u�W�F�N�g�̍��W
 * @param   radius  ��]������p�x
 * @return  ��]��̍��W
===========================================================================*/
Vector3f RotateQuaternion(Vector3f axis, Vector3f pos, float rad)
{
	Quaternion  S,Q1, Q2;
	Quaternion  posQuaternion = { pos.x, pos.y, pos.z ,0 };
	Vector3f     resultPos;

	if (axis.x == 0 && axis.y == 0 && axis.z == 0 ||
		rad == 0) {
		return pos;
	}
	//��]�p�N�I�[�^�j�I���쐬
	//S�͉��u��
	Q1 = MakeQuaternion(axis, rad);
	Q2 = MakeQuaternion(axis, -rad);
	//�|���Z
	MultiplyQuaternion(&S, &Q2, &posQuaternion);
	MultiplyQuaternion(&posQuaternion, &S, &Q1);
	
	resultPos.x = posQuaternion.x;
	resultPos.y = posQuaternion.y;
	resultPos.z = posQuaternion.z;

	return resultPos;
}
