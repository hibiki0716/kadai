#pragma once
#include "Vector2.h"
#include"GameScene.h"
class SceneManager;
//class GameScene;

class Box
{
public:

	// 1�}�X������̈ړ�����
	static constexpr float TIME_MOVE = 0.4f;

	// ���
	enum  class STATE {
		NONE,
		IDLE,
		MOVE,
		BACK_MOVE
	};

	Box(GameScene* scene);
	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void DrawTest(void);
	void Release(void);

	// ���W�̎擾
	Vector2 GetPos(void);

	// �����o�����
	void Push(DIR dir);

	// �ו��̉����o����̏Փ˔���
	bool IsPossiblePush(DIR dir);

	// ����
	bool IsStayStorage(void);

	// �����߂��@�\
	void BackMove(GameScene::History his);

	// �����߂����삪�\�����f
	bool IsEnableBack(void);

private:

	SceneManager* mManager;
	GameScene* mScene;

	// ���݂̍��W���
	STATE mState;

	int mImage;

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

	// �ו��u����̏�ɐݒu����Ă��邩����
	bool mIsStayStorage;

	// �����߂����߂̏��
	GameScene::History mHistry;

	// ��ԑJ��
	void ChangeState(STATE state);

};

