#pragma once

class Fader
{

public:

	enum class FADE_STATE
	{
		NONE
		, FADE_IN		// ���X�ɖ��]
		, FADE_OUT		// ���X�ɈÓ]
	};

	FADE_STATE GetState(void);
	bool IsEnd(void);
	void SetFade(FADE_STATE state);
	
	void Init(void);
	void Update(void);

private:

	FADE_STATE mState;

	// �P�x�l
	int mBrightValue;

	bool mIsEnd;

};

