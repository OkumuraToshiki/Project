#ifndef _CHARACTARBASE_H_
#define _CHARACTARBASE_H_
#include <string>
class BaseCharactar
{
private:

public:
	virtual ~BaseCharactar() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual std::string GetName() = 0;
};
#endif // !_CHARACTARBASE_H_