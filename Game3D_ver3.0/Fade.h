/*===========================================================================
  @file   Fade.h
  @brief  遷移時のフェード
  @author 奥村俊紀
  @date   2021/08/28
===========================================================================*/
#ifndef _FADE_H_
#define _FADE_H_
#include"main.h"
class FadeClass
{
public:
	FadeClass();
	~FadeClass();
	void Update();
	void Draw();
	void SetFadeIn(float time);
	void SetFadeout(float time);
	bool isFade();
private:
	float m_startTime;//初期化時間
	float m_time;//経過時間
	bool m_isFadeOut;//フラグ
};
#endif
