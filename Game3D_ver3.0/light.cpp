/*===========================================================================
  @file   Light.cpp
  @brief  ライト管理
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include "light.h"
/*===========================================================================
   コンストラクタ
===========================================================================*/
LightClass::LightClass()
{
	SetDirection(Vector3f(0.5f, -1.0f, 0.5f));
	SetDiffuse(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	SetAmbient(Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	SetSpecular(Vector4f(0.2f, 0.2f, 0.2f, 1.0f));
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
/*===========================================================================
   セット関数
===========================================================================*/
void LightClass::SetDirection(const Vector3f _dir)
{
	m_direction = _dir;
}

void LightClass::SetDiffuse(const Vector4f _diffuse)
{
	m_diffuse = _diffuse;
}

void LightClass::SetAmbient(const Vector4f _ambient)
{
	m_ambient = _ambient;
}

void LightClass::SetSpecular(const Vector4f _specular)
{
	m_specular = _specular;
}
