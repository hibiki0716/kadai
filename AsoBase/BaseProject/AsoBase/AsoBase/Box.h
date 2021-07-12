#pragma once
#include "Vector2.h"
#include"GameScene.h"
class SceneManager;
//class GameScene;

class Box
{
public:

	// 1マス当たりの移動時間
	static constexpr float TIME_MOVE = 0.4f;

	// 状態
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

	// 座標の取得
	Vector2 GetPos(void);

	// 押し出し問題
	void Push(DIR dir);

	// 荷物の押し出し先の衝突判定
	bool IsPossiblePush(DIR dir);

	// 判定
	bool IsStayStorage(void);

	// 巻き戻し機能
	void BackMove(GameScene::History his);

	// 巻き戻し操作が可能か判断
	bool IsEnableBack(void);

private:

	SceneManager* mManager;
	GameScene* mScene;

	// 現在の座標状態
	STATE mState;

	int mImage;

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

	// 荷物置き場の上に設置されているか判定
	bool mIsStayStorage;

	// 操作を戻すための情報
	GameScene::History mHistry;

	// 状態遷移
	void ChangeState(STATE state);

};

