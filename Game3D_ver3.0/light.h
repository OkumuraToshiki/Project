/*===========================================================================
  @file   Light.h
  @brief  ライト管理
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "VectorClass.h"
/*===========================================================================
 ライトクラス
===========================================================================*/
class LightClass
{
private:
	Vector4f m_diffuse;
	Vector4f m_ambient;
	Vector4f m_specular;
	Vector3f m_direction;
public:
	LightClass();
	~LightClass();

	const Vector3f& GetDirection()const;
	const Vector4f& GetDiffuse();
	const Vector4f& GetAmbient();
	const Vector4f& GetSpecular();
	void SetDirection(const Vector3f _dir);
	void SetDiffuse(const Vector4f _diffuse);
	void SetAmbient(const Vector4f _ambient);
	void SetSpecular(const Vector4f _specular);
};
#endif // !_LIGHT_H_
