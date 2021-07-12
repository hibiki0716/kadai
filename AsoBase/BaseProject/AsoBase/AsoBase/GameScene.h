#pragma once
#include<vector>
#include<string>
#include<stack>
#include<map>
#include "GameCommon.h"
#include "Vector2.h"
#include "SceneBase.h"

class SceneManager;
class Stage;
class Unit;
class Box;
class Storage;
class Fader;
class TimeLimit;

class GameScene : public SceneBase
{

public:

	// 最大ステージ数
	static constexpr int MAX_STAGE_NO = 6;

	// ステージクリアの表示時間
	static constexpr float TIME_CLEAR_ = 3.0f;

	// 状態
	enum  class STATE
	{
		GAME,
		CLEAR,
		CHANGE_STAGE
	};

	// 巻き戻し機能用構造体
	struct History
	{
		DIR dir;
		Vector2 uniPos;
		Box* box;
		Vector2 boxPos;
	};

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void UpdateGame(void);
	void UpdateClear(void);
	void UpdateChangeStge(void);
	void Draw(void) override;
	void DrawGame(void);
	void DrawClear(void);
	void DrawChangeStge(void);
	void DrawScore(void);
	void Release(void) override;
	
	Stage* GetStage(void);

	// 荷物との衝突判定
	Box* GetCollisionBox(Vector2 pos);

	// 荷物置き場との衝突判定
	Storage* GetCollisionStorage(Vector2 pos);

	// 演出用のフェードクラス
	Fader* mFader;

	// ステージ構成のファイルパスを取得
	std::string GetCsvPathGround(int StageNo);

	// ギミック構成のファイルパスを取得
	std::string GetCsvPathGimmick(int StageNo);

	// Bestそこあファイルパスを取得する関数を完成
	std::string GetCsvPathScore(void);

	// 操作履歴に登録
	void RegisHistory(DIR dir, Vector2 pos, Box* box);

	// 移動歩数をプラス
	void PlusCntMove(void);
	// 移動歩数をマイナス
	void MinusCntMove(void);

private:
	Stage* mStage;
	Unit* mUnit;
	Storage* mStorage;
	TimeLimit* mTimeLimit;
	Box* mBox;
	
	int mImageClear;

	float mStepClear;

	// 移動歩数
	int mCntMove;

	// 現在のステージBestスコア
	int mBestScore;

	// ステージごとのBestスコア
	std::map<int, int>mBestScores;

	// 動的配列
	std::vector<Box*> mBoxes;

	std::vector<Storage*> mStorages;

	// ステージ番号
	int mStageNo;

	STATE mState;

	// 巻き戻し機能
	std::stack<History> mHistoryBack;
	

	// ステージ遷移
	void ChangeStage(void);

	// コードでステージ設定
	void SetStage(void);

	// 外部ファイルを使用し、ステージ設定
	void LoadGimmickData(void);

	// 外部ファイルを使用してBestスコアを読み取る
	void LoadScore(void);

	// 現在のステージのBestスコアを取得
	int GetBestScore(void);

	// 状態遷移
	void ChangeState(STATE state);
};
