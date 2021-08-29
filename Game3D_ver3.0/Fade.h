/*===========================================================================
  @file   Fade.h
  @brief  �J�ڎ��̃t�F�[�h
  @author �����r�I
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
	float m_startTime;//����������
	float m_time;//�o�ߎ���
	bool m_isFadeOut;//�t���O
};
#endif
