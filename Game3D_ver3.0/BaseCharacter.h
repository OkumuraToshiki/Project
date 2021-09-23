/*===========================================================================
  @file   BaseCharacter.h
  @brief  キャラクターのベース
  @author 奥村俊紀
  @date   2021/09/19
===========================================================================*/
#ifndef _CHARACTARBASE_H_
#define _CHARACTARBASE_H_
#include <string>
class BaseCharacter
{
private:

public:
	virtual ~BaseCharacter() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual std::string GetName() = 0;
};
#endif // !_CHARACTARBASE_H_