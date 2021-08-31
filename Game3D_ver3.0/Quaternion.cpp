/*===========================================================================
  @file   Quaternion.h
  @brief  クオータニオン定義
  @author 奥村俊紀
  @date   2021/08/30
===========================================================================*/
#include "Quaternion.h"
/*===========================================================================
 * @brief   クォータニオンの掛け算
 * @param   pOut   計算結果
 * @param   pQ1    計算の左の項
 * @param   pQ2	   計算の右の項
 * @return  無し
===========================================================================*/
void MultiplyQuaternion(Quaternion* pOut, Quaternion* pQ1, Quaternion* pQ2)
{
	pOut->w = pQ1->w * pQ2->w - pQ1->x * pQ2->x - pQ1->y * pQ2->y - pQ1->z * pQ2->z;
	pOut->x = pQ1->w * pQ2->x + pQ2->w * pQ1->x + pQ1->y * pQ2->z - pQ1->z * pQ2->y;
	pOut->y = pQ1->w * pQ2->y + pQ2->w * pQ1->y + pQ1->z * pQ2->x - pQ1->x * pQ2->z;
	pOut->z = pQ1->w * pQ2->z + pQ2->w * pQ1->z + pQ1->x * pQ2->y - pQ1->y * pQ2->x;
}
/*===========================================================================
 * @brief   クォータニオン作成
 * @param   axis    回転させる軸
 * @param   radian  回転させる角度(ラジアン)
 * @return  作成したクォータニオン
===========================================================================*/
Quaternion MakeQuaternion(Vector3f axis, float rad)
{
	Quaternion quaternion;      // 作成するクォータニオン
	float halfSin, halfCos;      // 動かす角度の半分のsin,cos

	quaternion = { 0,0,0,0 };
	// 回転軸の長さが0の場合
	if(axis.Length() <= 0.0f)return quaternion;
	//正規化
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
 * @brief   クォータニオンによる回転
 * @param   axis    回転させたい軸
 * @param   pos     回転させるオブジェクトの座標
 * @param   radius  回転させる角度
 * @return  回転後の座標
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
	//回転用クオータニオン作成
	//Sは仮置き
	Q1 = MakeQuaternion(axis, rad);
	Q2 = MakeQuaternion(axis, -rad);
	//掛け算
	MultiplyQuaternion(&S, &Q2, &posQuaternion);
	MultiplyQuaternion(&posQuaternion, &S, &Q1);
	
	resultPos.x = posQuaternion.x;
	resultPos.y = posQuaternion.y;
	resultPos.z = posQuaternion.z;

	return resultPos;
}
