//=============================================================================
//
// �|���S������ [polygon.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

typedef struct {
	XMFLOAT2	fPos;		// ���W
	XMFLOAT2	fSize;		// �T�C�Y
	XMFLOAT2	fTexPos;	// �e�N�`�����W
	XMFLOAT2	fTexSize;	// �e�N�X�`���T�C�Y
	XMFLOAT4	fColor;		// �F
	float		fAngle;		// �p�x(�P�ʁF�x)

}PolygonInfo;
//*****************************************************************************
// �v���g�^�C�v�錾
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