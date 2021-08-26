
#pragma once
#include "main.h"
#include "polygon.h"
#include "Texture.h"
class CTitle
{
private:
	static const int          m_MaxCnt = 3;
	int                       m_MenuNum;
	PolygonInfo               m_Menu[m_MaxCnt];
	ID3D11ShaderResourceView* m_pTex[m_MaxCnt];
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
};
