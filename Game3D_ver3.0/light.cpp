/*===========================================================================
  light.cpp
�@���C�g�Ǘ�
===========================================================================*/
#include "light.h"
/*===========================================================================
   �R���X�g���N�^
===========================================================================*/
LightClass::LightClass()
{
}
/*===========================================================================
   �f�X�g���N�^
===========================================================================*/
LightClass::~LightClass()
{
}
/*===========================================================================
   �Q�b�g�֐�
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
   �Z�b�g�֐�
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
