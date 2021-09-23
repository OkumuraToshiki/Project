/*===========================================================================
  @file   Light.cpp
  @brief  ライト管理
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "light.h"
LightClass* LightClass::m_pLight = nullptr;
/*===========================================================================
   コンストラクタ
===========================================================================*/
LightClass::LightClass()
{
	m_direction = Vector3f(0.5f, -1.0f, -0.5f);
	m_diffuse = Vector4f(0.99f, 0.99f, 0.99f, 1.0f);
	m_ambient = Vector4f(0.5f, 0.5f, 0.5f, 1.0f);
	m_specular = Vector4f(0.2f, 0.9f, 0.2f, 1.0f);
}
/*===========================================================================
   デストラクタ
===========================================================================*/
LightClass::~LightClass()
{
}
/*===========================================================================
   ゲット関数
===========================================================================*/
const Vector3f& LightClass::GetDirection()const
{
	return m_direction;
}

const Vector4f& LightClass::GetDiffuse()
{
	return m_diffuse;
}

const Vector4f& LightClass::GetAmbient()
{
	return m_ambient;
}
const Vector4f& LightClass::GetSpecular()
{
	return m_specular;
}