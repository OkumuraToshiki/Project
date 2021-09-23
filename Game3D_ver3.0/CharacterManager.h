#ifndef _CHARACTARMANAGER_H_
#define _CHARACTARMANAGER_H_

#include <list>
#include "BaseCharacter.h"
class CharaFactory;
class CharacterMgr
{
private:
	CharaFactory* m_pFactory;
	std::list<BaseCharacter*> m_List;
public:
	CharacterMgr();
	~CharacterMgr();
	void Update();
	void Draw();
	void AddList(BaseCharacter* pChara);
};
#endif // !_CHARACTARMANAGER_H_
