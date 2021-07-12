#include<DxLib.h>
#include<cmath>
#include"GameCommon.h"
#include"SceneManager.h"
#include "TimeLimit.h"

TimeLimit::TimeLimit(SceneManager* manager){
	mSceneManager = manager;
}

void TimeLimit::Start(float sec){
	mLimitTime = sec;
}

void TimeLimit::Update(void){
	// mLimitTim‚ðŒ¸‚ç‚·
	mLimitTime -= mSceneManager->GetDeltaTime();
	if (mLimitTime < 0) {
		mLimitTime = 0;
	}
	
}

void TimeLimit::Draw(void){
	// mLimitTime‚ð•\Ž¦
	int x2 = SCREEN_SIZE_X - BLOCK_SIZE;
	int width = 200;
	DrawBox(x2 - width, 10, x2, 60, 0x000000, true);
	float time = mLimitTime;
	int color = 0x1e90ff;
	if (time < 30.0f) {
		color = 0xff6347;

		// ƒTƒCƒŒƒ“
		float alpha = (sin(time*5.0f)+1.0f)*0.5f;
		alpha = alpha * 110.0f;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, color, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	
	SetFontSize(32);
	DrawFormatString(850, 20, color,"%5.2f",time);
	
}

bool TimeLimit::IsTimeOver(void){

	return mLimitTime <= 0;
}
