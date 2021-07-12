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

	// 1マス当たりの移動時間
	static constexpr float TIME_MOVE = 0.4f;

	// アニメーション数
	static constexpr int CNT_ANIM = 4;

	// アニメーションスピード
	static constexpr int SPEED_SLOW_ANNIM = 8;

	// 状態
	enum  class STATE{
		NONE,
		IDLE,
		MOVE,
		BACK_MOVE
	};

	// コンストラクタ
	Unit(GameScene* scene);

	void Init(Vector2 mapPos);	// マップ座標
	void Update(void);
	void Draw(void);
	void Release(void);

	// 巻き戻し機能
	void BackMove(GameScene::History his);

	// 巻き戻し操作が可能か判断
	bool IsEnableBack(void);

private:

	SceneManager* mSceneManager;
	GameScene* mGameScene;

	// 通常画像
	int mPlayerImage[NUM_ANIM_Y][NUM_ANIM_X];
	// 押し出し画像
	int mImages[NUM_ANIM_Y][NUM_ANIM_X];

	// 現在の座標状態
	STATE mState;

	// 移動元座標
	Vector2 mMvSPos;

	// 移動先座標
	Vector2 mMvEPos;

	// 移動開始からの経過時間
	float mStepMove;

	// 移動方向
	DIR mDir;

	// スクリーン座標
	Vector2 mPos;

	// アニメーションカウント
	int animCnt;

	// 押し出し中
	bool mIsPushing;

	// 操作を戻すための情報
	GameScene::History mHistry;

	// 状態遷移
	void ChangeState(STATE state);
};

