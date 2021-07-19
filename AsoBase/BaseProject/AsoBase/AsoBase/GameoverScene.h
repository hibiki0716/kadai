#pragma once
#include"GameScene.h"
class SceneManager;

class GameoverScene : public SceneBase
{
public:
	GameoverScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	int mImage;

	int count;
};
