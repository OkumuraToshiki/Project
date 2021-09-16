#ifndef _CHARACTARBASE_H_
#define _CHARACTARBASE_H_

class CharaBaseClass
{
private:

public:
	virtual ~CharaBaseClass() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
#endif // !_CHARACTARBASE_H_