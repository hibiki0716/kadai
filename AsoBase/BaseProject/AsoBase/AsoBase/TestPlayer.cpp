#include <DxLib.h>
#include "TestPlayer.h"

void TestPlayer::Update(void){
	
	switch (mState)
	{
	/*case TestPlayer::STATE::NONE:
		break;*/
	case TestPlayer::STATE::IDLE:
		// �ҋ@���
		break;
	case TestPlayer::STATE::WALK:
		// �������
		break;
	case TestPlayer::STATE::RUN:
		// ������
		break;
	case TestPlayer::STATE::ATTACK:
		// �U�����
		break;
	case TestPlayer::STATE::DEAD:
		// ���S���
		break;
	default:
		break;
	}
}

// ��ԑJ��
void TestPlayer::ChangeState(STATE state){
	// ��Ԃ�ύX
	mState = state;

	// ��Ԃ��Ƃ̏��������������Ȃ�
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
