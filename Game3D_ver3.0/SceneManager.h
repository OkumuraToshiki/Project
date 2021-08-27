#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class BaseScene;
class SceneManager
{
private:
	BaseScene* m_pScene;
public:
	SceneManager();
	SceneManager(const SceneManager &) = delete;
	SceneManager &operator=(const SceneManager &) = delete;
	~SceneManager();

	void update();
	void draw() const;
};
#endif // !_SCENEMANAGER_H_