#include <DxLib.h>
#include "TestPlayer.h"

void TestPlayer::Update(void){
	
	switch (mState)
	{
	/*case TestPlayer::STATE::NONE:
		break;*/
	case TestPlayer::STATE::IDLE:
		// ‘Ò‹@ó‘Ô
		break;
	case TestPlayer::STATE::WALK:
		// •à‚«ó‘Ô
		break;
	case TestPlayer::STATE::RUN:
		// ‘–‚èó‘Ô
		break;
	case TestPlayer::STATE::ATTACK:
		// UŒ‚ó‘Ô
		break;
	case TestPlayer::STATE::DEAD:
		// €–Só‘Ô
		break;
	default:
		break;
	}
}

// ó‘Ô‘JˆÚ
void TestPlayer::ChangeState(STATE state){
	// ó‘Ô‚ğ•ÏX
	mState = state;

	// ó‘Ô‚²‚Æ‚Ì‰Šúˆ—‚ğ‚¨‚±‚È‚¤
	switch (mState)
	{
	case TestPlayer::STATE::NONE:
		break;
	case TestPlayer::STATE::IDLE:
		break;
	case TestPlayer::STATE::WALK:
		break;
	case TestPlayer::STATE::RUN:
		break;
	case TestPlayer::STATE::ATTACK:
		break;
	case TestPlayer::STATE::DEAD:
		break;
	default:
		break;
	}
}
