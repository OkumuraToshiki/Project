#ifndef _BASESCENE_H_
#define _BASESCENE_H_
class BaseScene
{
private:
protected:
	template<typename T>
	BaseScene *makeScene();
public:
	virtual ~BaseScene() {}
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
};
#endif // !_BASESCENE_H_
