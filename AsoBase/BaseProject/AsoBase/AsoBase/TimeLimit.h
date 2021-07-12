#pragma once

class SceneManager;

class TimeLimit
{
public:
	TimeLimit(SceneManager* manager);

	void Start(float sec);
	void Update(void);
	void Draw(void);
	
	bool IsTimeOver(void);

private:

	SceneManager* mSceneManager;
	float mLimitTime;
};

