/*===========================================================================
  FileName.hpp
  �t�@�C�����Ǘ�
===========================================================================*/
#pragma once
#include "main.h"
/*===========================================================================
	���f���̎��
===========================================================================*/
enum eModel
{
	MODEL_BALL,
	MODEL_KNIGHT,
	MODEL_ENEMY,
	MODEL_BOX,
	MODEL_SKY,
	MODEL_MAX
};
/*===========================================================================
	�e�N�X�`���̎��
===========================================================================*/
enum eTexture
{
	TEXTURE_FIELD,
	TEXTURE_MAX
};
/*===========================================================================
	fbx�t�@�C����
===========================================================================*/
static LPCSTR pszModelPath[MODEL_MAX] = {
	"data/model/X_wing/X_wing.fbx",
	"data/model/knight/DarkKnight_low.fbx",
	"data/model/fellguard/fellguard.fbx",
	"data/model/box.fbx",
	"data/model/sky/sky.fbx"
};
static LPCSTR pszTexPath[TEXTURE_MAX] = {
	"data/texture/bullet000.png"
};