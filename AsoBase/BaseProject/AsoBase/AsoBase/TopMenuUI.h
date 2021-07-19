#pragma once
class StageSelect;
class HightScoreMenuUI;
class TopMenuUI
{
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	HightScoreMenuUI* mHightScoreMenuUI;
};

