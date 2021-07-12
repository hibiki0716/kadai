#pragma once
#include "Vector2.h"
#include"GameScene.h"

#define NUM_ANIM_X 3
#define NUM_ANIM_Y 4
#define IMG_SIZE 32

class SceneManager;
class GameScene;

class Unit
{
public:

	// 1�}�X������̈ړ�����
	static constexpr float TIME_MOVE = 0.4f;

	// �A�j���[�V������
	static constexpr int CNT_ANIM = 4;

	// �A�j���[�V�����X�s�[�h
	static constexpr int SPEED_SLOW_ANNIM = 8;

	// ���
	enum  class STATE{
		NONE,
		IDLE,
		MOVE,
		BACK_MOVE
	};

	// �R���X�g���N�^
	Unit(GameScene* scene);

	void Init(Vector2 mapPos);	// �}�b�v���W
	void Update(void);
	void Draw(void);
	void Release(void);

	// �����߂��@�\
	void BackMove(GameScene::History his);

	// �����߂����삪�\�����f
	bool IsEnableBack(void);

private:

	SceneManager* mSceneManager;
	GameScene* mGameScene;

	// �ʏ�摜
	int mPlayerImage[NUM_ANIM_Y][NUM_ANIM_X];
	// �����o���摜
	int mImages[NUM_ANIM_Y][NUM_ANIM_X];

	// ���݂̍��W���
	STATE mState;

	// �ړ������W
	Vector2 mMvSPos;

	// �ړ�����W
	Vector2 mMvEPos;

	// �ړ��J�n����̌o�ߎ���
	float mStepMove;

	// �ړ�����
	DIR mDir;

	// �X�N���[�����W
	Vector2 mPos;

	// �A�j���[�V�����J�E���g
	int animCnt;

	// �����o����
	bool mIsPushing;

	// �����߂����߂̏��
	GameScene::History mHistry;

	// ��ԑJ��
	void ChangeState(STATE state);
};

