#include "DxLib.h"
#include "Fader.h"

Fader::FADE_STATE Fader::GetState(void)
{
	return mState;
}

bool Fader::IsEnd(void)
{
	return mIsEnd;
}

void Fader::SetFade(FADE_STATE state)
{
	mState = state;
	if (mState != FADE_STATE::NONE){
		mIsEnd = false;
	}
}

void Fader::Init(void)
{
	mState = FADE_STATE::NONE;
	mBrightValue = 255;
	mIsEnd = true;
}

void Fader::Update(void)
{

	if (mIsEnd){
		return;
	}

	switch (mState){
	case FADE_STATE::NONE:
		return;
	case FADE_STATE::FADE_IN:
		mBrightValue += 5;
		if (mBrightValue > 255){
			// フェード終了
			mBrightValue = 255;
			mIsEnd = true;
		}
		break;

	case FADE_STATE::FADE_OUT:
		mBrightValue -= 5;
		if (mBrightValue < 0){
			// フェード終了
			mBrightValue = 0;
			mIsEnd = true;

		}
		break;

	default:
		return;
	}

	SetDrawBright(mBrightValue, mBrightValue, mBrightValue);

}
