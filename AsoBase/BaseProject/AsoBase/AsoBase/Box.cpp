#include <DxLib.h>
#include "GameScene.h"
#include "SceneManager.h"
#include "GameCommon.h"
#include "Stage.h"
#include "Box.h"

Box::Box(GameScene* scene) {
	mScene = scene;
	mManager = scene->GetSceneManager();
}

void Box::Init(Vector2 mapPos){
	mImage = LoadGraph("Image/Box.png", true);

	// �}�b�v���W���X�N���[�����W�֕ϊ�
	mPos = {
		mapPos.x * BLOCK_SIZE,
		mapPos.y * BLOCK_SIZE
	};

	mMvSPos = { 0,0 };
	mMvEPos = { 0,0 };

	mStepMove = 0.0f;

	mDir = DIR::DOWN;

	mIsStayStorage = false;

	ChangeState(STATE::IDLE);
}

void Box::Update(void){

	switch (mState)
	{
	case Box::STATE::IDLE:

		break;
	case Box::STATE::MOVE:
	case Box::STATE::BACK_MOVE:
	{
		mStepMove += mManager->GetDeltaTime();
		float t = mStepMove / TIME_MOVE;
		mPos = Vector2::Lerp(mMvSPos, mMvEPos, t);
		if (t >= 1.0f) {
			mPos = mMvEPos;
			ChangeState(STATE::IDLE);
			return;
		}
		break;
	}
	default:
		break;
	}
}

void Box::Draw(void){
	
	// �ו��u����̏�ɉו����ݒu���ꂽ��
	// ���ꂪ�킩��悤�ɉ��o
	int x = GAME_AREA_X + mPos.x;
	int y = GAME_AREA_Y + mPos.y;
	if (mIsStayStorage == true) {
		// �ݒu����Ă���
		DrawGraph(x, y,mImage, true);
		SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		DrawGraph(x, y, mImage, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		// �ݒu����Ă��Ȃ�
		DrawGraph(x, y,mImage, true);
	}

	// �F�̍���
	//DrawTest();
}

void Box::DrawTest(void){
	int miniSize = 4;
	int size = BLOCK_SIZE * miniSize;

	// �`���Ԃ��쐬
	int img01 = MakeScreen(size, size, false);

	// �쐬�����`���Ԃ�`��Ώ�
	SetDrawScreen(img01);

	int c01 = 255 / (BLOCK_SIZE * 2);
	for (int y = 0; y < BLOCK_SIZE; y++) {
		for (int x = 0; x < BLOCK_SIZE; x++) {
			int tmp = c01 * (x + y);
			DrawBox(x * miniSize, y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true);
		}
	}
	// �`��Ώۂ𗠉��
	SetDrawScreen(DX_SCREEN_BACK);
	// ����ʂɃI���W�i���̕`���Ԃ��쐬
	DrawGraph(20, 20, img01, true);

	// �`���Ԃ��쐬
	int img02 = MakeScreen(size, size, false);

	// �쐬�����`���Ԃ�`��Ώ�
	SetDrawScreen(img02);

	int c02 = 255 / BLOCK_SIZE;
	for (int y = 0; y < BLOCK_SIZE; y++) {
		for (int x = 0; x < BLOCK_SIZE; x++) {
			int tmp = c02 * x ;
			DrawBox(x * miniSize, y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true);
		}
	}
	// �`��Ώۂ𗠉��
	SetDrawScreen(DX_SCREEN_BACK);
	// ����ʂɃI���W�i���̕`���Ԃ��쐬
	DrawGraph(200, 20, img02, true);

	// �������̇@�@�F�̏�Z
	int imgMix01 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix01);
	DrawGraph(0, 0, img01, true);

	// DxLib�̐F�̏�Z
	SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
	DrawGraph(0, 0, img02, true);

	// �u�����h���[�h���I�t
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �`��Ώۂ𗠉��
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(400, 20, imgMix01, true);


	// �������̇A�@�F�̏�Z
	int imgMix02 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix02);

	for (int y = 0; y < BLOCK_SIZE; y++) {
		for (int x = 0; x < BLOCK_SIZE; x++) {
			float tmp1 = c01 * (x + y);
			float tmp2 = c02 * x;
			// �F�̏�Z
			float tmp = (tmp1 / 255.0f) * (tmp2 / 255.0f) * 255.0f;
			DrawBox(x * miniSize, y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true);
		}
	}

	// �`��Ώۂ𗠉��
	SetDrawScreen(DX_SCREEN_BACK);
	// ����ʂɃI���W�i���̕`���Ԃ��쐬
	DrawGraph(600, 20, imgMix02, true);

	
	// �������̇B�@�F�̉��Z
	int imgMix03 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix03);
	DrawGraph(0, 0, img01, true);

	// DxLib�̐F�̏�Z
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawGraph(0, 0, img02, true);

	// �u�����h���[�h���I�t
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �`��Ώۂ𗠉��
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(400, 200, imgMix03, true);

	// �������̇C�@�F�̉��Z
	int imgMix04 = MakeScreen(size, size, false);
	SetDrawScreen(imgMix04);

	for (int y = 0; y < BLOCK_SIZE; y++) {
		for (int x = 0; x < BLOCK_SIZE; x++) {
			float tmp1 = c01 * (x + y);
			float tmp2 = c02 * x;
			// �F�̉��Z
			float tmp = ((tmp1 / 255.0f) + (tmp2 / 255.0f)) * 255.0f;
			if (tmp > 255.0f) {
				tmp = 255.0f;
			}
			DrawBox(x * miniSize, y * miniSize,
				(x * miniSize) + miniSize,
				(y * miniSize) + miniSize,
				GetColor(tmp, tmp, tmp), true);
		}
	}

	// �`��Ώۂ𗠉��
	SetDrawScreen(DX_SCREEN_BACK);
	// ����ʂɃI���W�i���̕`���Ԃ��쐬
	DrawGraph(600, 200, imgMix04, true);
}

void Box::Release(void){
	DeleteGraph(mImage);
}

Vector2 Box::GetPos(void){
	return mPos;
}

void Box::Push(DIR dir){
	// �����̕ێ�
	mDir = dir;
	// �ړ���ԂɑJ�ڂ�����
	ChangeState(STATE::MOVE);
}

bool Box::IsPossiblePush(DIR dir){

	// �ړ���̃}�b�v���W
	Vector2 mapPos = mPos;
	mapPos.x /= BLOCK_SIZE;
	mapPos.y /= BLOCK_SIZE;

	// �ړ�����W
	switch (dir)
	{
	case DIR::DOWN:
		mapPos.y += 1;
		break;
	case DIR::LEFT:
		mapPos.x -= 1;
		break;
	case DIR::RIGHT:
		mapPos.x += 1;
		break;
	case DIR::UP:
		mapPos.y -= 1;
		break;
	}
	
	// �ړ���̕ǂƂ̏Փ˃`�F�b�N
	if (mScene->GetStage()->IsCollositiom(mapPos) == true) {
		return false;
	}

	// �ړ���̉ו��Ƃ̏Փ˃`�F�b�N
	Vector2 mvEPos =  mapPos;
	mvEPos.x *= BLOCK_SIZE;
	mvEPos.y *= BLOCK_SIZE;
	Box* box = mScene->GetCollisionBox(mvEPos);
	if (box != nullptr) {
		return false;
	}

	return true;
}

bool Box::IsStayStorage(void){
	return mIsStayStorage;
}

void Box::BackMove(GameScene::History his){
	mHistry = his;
	ChangeState(STATE::BACK_MOVE);
}

bool Box::IsEnableBack(void){
	return mState == STATE::IDLE;
}

void Box::ChangeState(STATE state){
	// ��Ԃ�ύX
	mState = state;

	switch (mState)
	{
	case Box::STATE::IDLE: {
		// �ו��u���ꔻ��
		Storage* storage = mScene->GetCollisionStorage(mPos);
		if (storage != nullptr) {
			mIsStayStorage = true;
		}
		else {
			mIsStayStorage = false;
		}

		break;
	}
	case Box::STATE::MOVE: {
		// ���`��Ԃɂ��ړ��������쐬


		// �o�ߎ��Ԃ�������
		mStepMove = 0.0f;
		// �ړ������W�����ݍ��W��
		mMvSPos = mMvEPos = mPos;

		// �ړ�����W
		switch (mDir)
		{
		case DIR::DOWN:
			mMvEPos.y += BLOCK_SIZE;
			break;
		case DIR::LEFT:
			mMvEPos.x -= BLOCK_SIZE;
			break;
		case DIR::RIGHT:
			mMvEPos.x += BLOCK_SIZE;
			break;
		case DIR::UP:
			mMvEPos.y -= BLOCK_SIZE;
			break;
		}

		Vector2 mapPos = { 0,0 };
		mapPos.x = mMvEPos.x / BLOCK_SIZE;
		mapPos.y = mMvEPos.y / BLOCK_SIZE;

		// �ړ���̏Փ˃`�F�b�N
		if (mScene->GetStage()->IsCollositiom(mapPos) == true) {
			ChangeState(STATE::IDLE);
			return;
		}

		break;
	}
	case Box::STATE::BACK_MOVE: {
		// �o�ߎ��Ԃ�������
		mStepMove = 0.0f;
		// 
		//mHistry;
		// �ړ������W
		mMvSPos = mPos;
		// �ړ�����W
		mMvEPos = mHistry.boxPos;

		mDir = mHistry.dir;

		break;
	}
	
	default:
		break;
	}
}
