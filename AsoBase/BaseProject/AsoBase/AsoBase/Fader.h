#pragma once

class Fader
{

public:

	enum class FADE_STATE
	{
		NONE
		, FADE_IN		// 徐々に明転
		, FADE_OUT		// 徐々に暗転
	};

	FADE_STATE GetState(void);
	bool IsEnd(void);
	void SetFade(FADE_STATE state);
	
	void Init(void);
	void Update(void);

private:

	FADE_STATE mState;

	// 輝度値
	int mBrightValue;

	bool mIsEnd;

};

