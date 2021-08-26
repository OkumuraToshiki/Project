//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

typedef struct {
	XMFLOAT2	fPos;		// 座標
	XMFLOAT2	fSize;		// サイズ
	XMFLOAT2	fTexPos;	// テクチャ座標
	XMFLOAT2	fTexSize;	// テクスチャサイズ
	XMFLOAT4	fColor;		// 色
	float		fAngle;		// 角度(単位：度)

}PolygonInfo;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPolygon(ID3D11Device* pDevice);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(ID3D11DeviceContext* pDeviceContext);
void SetPolygonTexture(ID3D11ShaderResourceView* pTexture);
void SetPolygonPos(float fX, float fY);
void SetPolygonSize(float fScaleX, float fScaleY);
void SetPolygonAngle(float fAngle);
void SetPolygonUV(float fU, float fV);
void SetPolygonFrameSize(float fWidth, float fHeight);
void SetPolygonColor(float fRed, float fGreen, float fBlue);
void SetPolygonAlpha(float fAlpha);
void SetDrawPolygon(PolygonInfo tPolygon, ID3D11ShaderResourceView* pTexture);