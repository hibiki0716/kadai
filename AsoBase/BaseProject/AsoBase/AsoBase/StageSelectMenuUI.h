#pragma once
class GameScene;

class StageSelectMenuUI
{
public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Close(void);

private:

	GameScene* mGameScene;
};

