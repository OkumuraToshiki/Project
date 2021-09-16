/*===========================================================================
  FileName.hpp
  ファイル名管理
===========================================================================*/
#pragma once
#include "main.h"
/*===========================================================================
	モデルの種類
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
	テクスチャの種類
===========================================================================*/
enum eTexture
{
	TEXTURE_FIELD,
	TEXTURE_MAX
};
/*===========================================================================
	fbxファイル名
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