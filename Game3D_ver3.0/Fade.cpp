/*===========================================================================
  @file   Fade.cpp
  @brief  遷移時のフェード
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#include"Fade.h"
#include"polygon.h"
FadeClass::FadeClass()
{
	m_startTime = 0.0f;
	m_time = 0.0f;
	m_isFadeOut = false;
}
FadeClass::~FadeClass()
{
}
void FadeClass::Update()
{
	if (m_time > 0.0f)
	{
		m_time -= 1.0f / 60;
		if (m_time < 0.0f)
		{
			m_time = 0;
		}
	}
}
void FadeClass::Draw()
{
	SetPolygonAngle(0);
	SetPolygonSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetPolygonTexture(NULL);
	SetPolygonColor(0, 0, 0);
	SetPolygonPos(0, 0);

	//fade out
	if (m_isFadeOut)
	{
		SetPolygonAlpha(1.0 - (m_time / m_startTime));//現在の時間を最大値で割る０から１
	}
	else {
		//fade in
		SetPolygonAlpha(m_time / m_startTime);
	}
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());
}
void FadeClass::SetFadeIn(float time)
{
	m_startTime = m_time = time;
	m_isFadeOut = false;
}
void FadeClass::SetFadeout(float time)
{
	m_startTime = m_time = time;
	m_isFadeOut = true;
}
bool FadeClass::isFade()
{
	return m_time > 0;
}