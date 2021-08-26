#include "Menu.h"
#include "input.h"
#include "debugproc.h"
static LPCWSTR c_tFileName[3] = {
	L"data/texture/pause002.jpg",	// 始める
	L"data/texture/pause004.jpg",	// タイトルに戻る
	L"data/texture/pause001.jpg"
};
HRESULT CTitle::Init()
{
	HRESULT  hr;
	m_MenuNum = 0;
	for (int i = 0; i < m_MaxCnt; i++)
	{
		m_Menu[i].fSize = XMFLOAT2(100.0f, 100.0f);
		m_Menu[i].fPos = XMFLOAT2(-300.0f, 0.0f - i * m_Menu[i].fSize.y);
		m_Menu[i].fTexPos = XMFLOAT2(0.0f, 0.0f);
		m_Menu[i].fTexSize = XMFLOAT2(1.0f, 1.0f);
		m_Menu[i].fColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		m_Menu[i].fAngle = 0.0f;
	}
	
	hr = CreateTextureFromFile(GetDevice(), c_tFileName[0], &m_pTex[0]);
	hr = CreateTextureFromFile(GetDevice(), c_tFileName[1], &m_pTex[1]);
	hr = CreateTextureFromFile(GetDevice(), c_tFileName[2], &m_pTex[2]);
	
	return hr;
}
void CTitle::Uninit()
{
	for (int i = 0; i < m_MaxCnt; i++)
	{
		SAFE_RELEASE(m_pTex[i]);
	}
}
void CTitle::Update()
{
	if (GetKeyTrigger(VK_W))
	{
		LoopMinus(m_MenuNum, m_MaxCnt);
	}
	if (GetKeyTrigger(VK_S))
	{
		LoopPlus(m_MenuNum, m_MaxCnt);
	}
	
}
void CTitle::Draw()
{
	for (int i = 0; i < m_MaxCnt; i++)
	{
		if (i == m_MenuNum)
		{
			m_Menu[i].fColor.y = 0.0f;
			m_Menu[i].fColor.w = 1.0f;
		}
		else
		{
			m_Menu[i].fColor.y = 1.0f;
			m_Menu[i].fColor.w = 0.2f;
		}
		SetDrawPolygon(m_Menu[i], m_pTex[i]);
	}
	SetPolygonAlpha(1.0f);
}