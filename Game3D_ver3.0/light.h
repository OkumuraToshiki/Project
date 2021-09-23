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
	static LightClass* m_pLight;
public:
	LightClass();
	~LightClass();

	const Vector3f& GetDirection()const;
	const Vector4f& GetDiffuse();
	const Vector4f& GetAmbient();
	const Vector4f& GetSpecular();
	
	static void Set(LightClass* pLight) { m_pLight = pLight; }
	static LightClass* Get() { return m_pLight; }
};
#endif // !_LIGHT_H_
