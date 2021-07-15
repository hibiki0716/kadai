#include <DxLib.h>
#include<vector>
#include<string>
#include<fstream>
#include<stack>
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Unit.h"
#include "Box.h"
#include "Storage.h"
#include "Vector2.h"
#include"Fader.h"
#include"Utility.h"
#include"TimeLimit.h"
#include"PopupUIBase.h"
#include "GameScene.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager){
	mStageNo = 1;
	ChangeState(STATE::GAME);
	mFader = new Fader();
	mFader->Init();

	mTimeLimit = new TimeLimit(manager);
	
	mPopupUiBase = new PopupUIBase(this);
	mPopupUiBase->Init({ 100,100 });
}

/// <summary>
/// 初期化
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Init(void){

	// ステージ
	mStage = new Stage(this);
	mStage->Init(mStageNo);
	
	// ステージ
	//SetStage();

	// 外部ファイルを使用し、ステージ設定
	LoadGimmickData();

	LoadScore();

	mImageClear = LoadGraph("Image/Congratulations.png");
	mStepClear = 0.0f;

	// 時間制限
	mTimeLimit->Start(mStageNo * 60);

	// 移動歩数
	mCntMove = 0;

	mBestScore = 0;
}

/// <summary>
/// 更新ステップ
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Update(void){

	if (keyTrgDown[KEY_SYS_START]){
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
	}

	switch (mState)
	{
	case GameScene::STATE::GAME: 
		UpdateGame();
		break;
	case GameScene::STATE::CLEAR:
		UpdateClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		UpdateChangeStge();
		break;
	
	}
}

void GameScene::UpdateGame(void){
	
	// メニューが開いているか
	if (mPopupUiBase->IsOpen() == true) {
		mPopupUiBase->Update();
		// Mボタンが押されたらメニュ画面を閉じる
		if (keyTrgDown[KEY_P1_B]) {
			mPopupUiBase->Close();
		}
		// 処理を中断
		return;
	}
	else {
		// Mボタンが押されたらメニュ画面を開く
		if (keyTrgDown[KEY_P1_B]) {
			mPopupUiBase->Open();
		}
	}
		
	// ステージ
	mStage->Update();
	// Unit
	mUnit->Update();

	// 動的配列
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Update();
	}

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Update();
	}

	// 操作を戻すNキー
	if (keyTrgDown[ KEY_P1_A ] && mHistoryBack.size() > 0
		&& mUnit->IsEnableBack()) {

		// 最後の操作情報を取得
		History his = mHistoryBack.top();

		if (his.box != nullptr) {
			// 荷物を移動させた
			his.box->BackMove(his);
		}

		// 最後の操作情報をユニットに渡して巻き戻し処理をさせる
		mUnit->BackMove(his);
	
		// 最後の操作情報を削除
		mHistoryBack.pop();

		MinusCntMove();
	}

	// 時間制限
	mTimeLimit->Update();
	if (mTimeLimit->IsTimeOver() == true) {
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER,true);
		return;
	}

	// クリア判定
	bool isClear = true;
	size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		if (mBoxes[i]->IsStayStorage() == false) {
			isClear = false;
			break;
		}
	}

	if (isClear == true) {
		if (mStageNo >= MAX_STAGE_NO) {
			// ゲームオーバー画面へ遷移
			mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
		}
		else {
			// 次のステージへ
			//ChangeStage();
			ChangeState(STATE::CLEAR);
			return;
		}

	}
}

void GameScene::UpdateClear(void){
	mStepClear+= mSceneManager->GetDeltaTime();
	if (mStepClear > TIME_CLEAR_) {
		
		ChangeState(STATE::CHANGE_STAGE);
		return;
	}
}

void GameScene::UpdateChangeStge(void){
	mFader->Update();

	Fader::FADE_STATE state = mFader->GetState();

	switch (state)
	{
	case Fader::FADE_STATE::FADE_OUT:
		// 段々暗くする
		if (mFader->IsEnd() == true) {
			// ステージ切り替え
			ChangeStage();
			// 徐々に明るくする
			mFader->SetFade(Fader::FADE_STATE::FADE_IN);
		}

		break;
	case Fader::FADE_STATE::FADE_IN:
		// 段々明るくする
		if (mFader->IsEnd() == true) {
			mFader->SetFade(Fader::FADE_STATE::NONE);
			ChangeState(STATE::GAME);
		}
		break;
	
	}

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name=""></param>
void GameScene::Draw(void){

	SetDrawScreen(DX_SCREEN_BACK);

	// 画面のクリア
	ClearDrawScreen();

	switch (mState)
	{
	case GameScene::STATE::GAME:
		DrawGame();
		break;
	case GameScene::STATE::CLEAR:
		DrawClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		DrawChangeStge();
		break;

	}
}

void GameScene::DrawGame(void){
	// ステージ
	mStage->Draw();

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Draw();
	}
	// Unit
	mUnit->Draw();

	// 動的配列
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Draw();
	}

	// 時間制限
	mTimeLimit->Draw();

	// スコア表示
	DrawScore();

	// メニューが開かれているとき描画する
	if (mPopupUiBase->IsOpen() == true) {
		mPopupUiBase->Draw();
	}

}

void GameScene::DrawClear(void) {
	DrawGame();

	// ステージクリアの画面表示
	DrawGraph(SCREEN_SIZE_X / 2 - (500 / 2)
		, SCREEN_SIZE_Y / 2
		, mImageClear, true);

}

void GameScene::DrawChangeStge(void){
	DrawGame();
}

void GameScene::DrawScore(void){
	// プレイヤーっ操作に応じて、スコアを増加させる
	// 移動したら歩数が増える、戻したら歩数が減る
	//DrawFormatString(20, 20, 0xffffff, "%d",mCntMove);

	int x1, x2;
	int y1 = 10;
	int width = 100;
	int height = 300;
	int y2 = 60;
	int charX;
	int charY = 20;

	// ベストスコア
	x1 = 300;
	x2 = x1 + width;
	
	DrawBox(x1, y1, x1+width, y2, 0x000000,true);
	DrawBox(x2+50, y1, x2 + 150, y2, 0x000000, true);

	charX = ((x1 + x2) / 2) - 10;
	SetFontSize(32);
	DrawFormatString(charX, charY, 0xffffff, "%d",mBestScore);

	SetFontSize(20);
	DrawFormatString(x1, y1, 0xffffff, "BestScore");
}

/// <summary>
/// リソース解放
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Release(void){
	// ステージ
	mStage->Release();
	delete mStage;
	// Unit
	mUnit->Release();
	delete mUnit;

	// 動的配列
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Release();
		delete mBoxes[i];
	}
	// 動的配列のサイズをゼロにする
	mBoxes.clear();

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Release();
		delete mStorages[i];
	}
	mStorages.clear();

	DeleteGraph(mImageClear);

	// 操作履歴
	//while (mHistoryBack.size > 0) {
	//	/*auto tmp = mHistoryBack.top;
	//	delete tmp;*/

	//	mHistoryBack.pop();
	//}
	//mHistoryBack = std::stack<History>();

}

Stage* GameScene::GetStage(void){

	return mStage;
}

Box* GameScene::GetCollisionBox(Vector2 pos){
	Box* ret = nullptr;

	Vector2 boxPos;
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		boxPos = mBoxes[i]->GetPos();
		// 座標の比較
		if (pos.x == boxPos.x && pos.y == boxPos.y) {
			// 座標が一致したらBoxを戻り値にする
			ret = mBoxes[i];
			break;
		}
		
	}

	return ret;
}

Storage* GameScene::GetCollisionStorage(Vector2 pos){
	// 引数の座標と一致する荷物置き場を検索
	// 見つからなければ、nullptrを返す
	Storage* ret = nullptr;

	Vector2 storagePos;
	int size = mStorages.size();
	for (int i = 0; i < size; i++) {
		storagePos = mStorages[i]->GetPos();
		// 座標の比較
		if (pos.x == storagePos.x && pos.y == storagePos.y) {
			// 座標が一致したらBoxを戻り値にする
			ret = mStorages[i];
			break;
		}

	}
	return ret;
}

std::string GameScene::GetCsvPathGround(int StageNo){
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(StageNo);
	ret += "/";
	ret += FILE_NAME_GROUND;

	return ret;
}

std::string GameScene::GetCsvPathGimmick(int StageNo){
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(StageNo);
	ret += "/";
	ret += FILE_NAME_GIMMICK;

	return ret;
}

std::string GameScene::GetCsvPathScore(void){
	std::string ret = "";

	ret += "StageData/";
	ret += FILE_NAME_SCORE;

	return ret;
}

void GameScene::RegisHistory(DIR dir, Vector2 pos, Box* box){
	Vector2 boxPos = { 0,0 };
	if (box != nullptr) {
		boxPos = box->GetPos();

	}

	History his = {dir,pos,box,boxPos};
	mHistoryBack.push(his);
}

void GameScene::PlusCntMove(void){
	mCntMove++;
}

void GameScene::MinusCntMove(void){
	mCntMove--;
}

void GameScene::ChangeStage(void){
	Release();

	// 次のステージへ行くため
	mStageNo++;
	Init();
}

void GameScene::SetStage(void){

	// 荷物
	Box* tmpBox;

	// 荷物置き場
	Storage* tmpStorage;


	switch (mStageNo)
	{
	case 1:
		// Unit
		mUnit = new Unit(this);
		mUnit->Init({ 10,10 });

		tmpBox = new Box(this);
		tmpBox->Init({ 11,10 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init({ 18,10 });
		mBoxes.push_back(tmpBox);
		
		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 11,11 });
		mStorages.push_back(tmpStorage);
		break;
	case 2:
		// Unit
		mUnit = new Unit(this);
		mUnit->Init({ 10,6 });

		// 荷物
		tmpBox = new Box(this);
		tmpBox->Init({ 11,7 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init({ 18,8 });
		mBoxes.push_back(tmpBox);

		// 荷物置き場
		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,11 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,12 });
		mStorages.push_back(tmpStorage);
		break;
	default:
		break;
	}
}

void GameScene::LoadGimmickData(void){
	
	// ファイルパスを取得
	std:: string filePath = GetCsvPathGimmick(mStageNo);

	// ファイルを読み込む
	std::ifstream ifs(filePath);

	// 1行ずつ読み込む
	int y = 0;
	std::string line;

	// 荷物
	Box* tmpBox;

	// 荷物置き場
	Storage* tmpStorage;

	while (getline(ifs, line)) {

		// Yで分割されたline
		std::vector<std::string> strvec = Utility::Split(line, ',');

		// Xで分割されたstrvec

		// mMapに値を代入して、
		// ステージを作成
		for (int x = 0; x < strvec.size(); x++) {
			int chipNo = stoi(strvec[x]);
			switch (chipNo)
			{

			case 4:
				// 荷物
				tmpBox = new Box(this);
				tmpBox->Init({ x,y });
				mBoxes.push_back(tmpBox);
				break;

			case 5:
				// 荷物置き場
				tmpStorage = new Storage(this);
				tmpStorage->Init({ x,y });
				mStorages.push_back(tmpStorage);
				break;
			case 6:
				// ユニット
				// Unit
				mUnit = new Unit(this);
				mUnit->Init({ x,y });
				break;
			}
		}
		y++;
	}

	if (true) {}
}

void GameScene::LoadScore(void){

	// ファイルパスを取得
	std::string filePath = GetCsvPathScore();

	// ファイルを読み込む
	std::ifstream ifs(filePath);

	// 1行ずつ読み込む
	int y = 0;
	std::string line;

	while (getline(ifs, line)) {

		// Yで分割されたline
		std::vector<std::string> strvec = Utility::Split(line, ',');
		
		int StageNo = stoi(strvec[0]);
		int bestScore = stoi(strvec[1]);

		mBestScores.emplace(StageNo,bestScore);
	}

}

void GameScene::SaveScore(void){
	// SaveScore関数をどこで呼び出すか
	// 必要な条件分も記述
	// ※Bestスコアよりも、ステージクリア時のスコアの方が小さい場合

	// 動的配列内のBestスコア更新
	if (0 < mBestScores.count(mStageNo)) {
		// mapの中にKeyがある場合
		mBestScores[mStageNo] = mCntMove;
	}
	else {
		// mapの中にKeyがない場合
		mBestScores.emplace(mStageNo, mCntMove);
	}
	// ファイルパスを取得
	std::string filePath = GetCsvPathScore();

	// ファイル全体への書き込み
	std::ofstream ofs = std::ofstream(filePath);

	// 行ごとにファイルごとに書き込む
	std::string line;

	for (std::pair<int,int> p : mBestScores) {
		line = "";
		line += std::to_string(p.first);
		line += ",";
		line += std::to_string(p.second);
		ofs << line<<std::endl;
	}
	ofs.close();
}

int GameScene::GetBestScore(void){
	int ret = 999;
	//auto find = mBestScores.find(mStageNo);

	if (0 <mBestScores.count(mStageNo)) {
		// mapに対象のキーがなかった
		std::map<int, int>::iterator it = mBestScores.find(mStageNo);
		ret = it->second;
	}

	// 現在のステージのBestスコア
	return ret;
}

void GameScene::ChangeState(STATE state){
	mState = state;
	switch (state)
	{
	case GameScene::STATE::GAME:
		break;
	case GameScene::STATE::CLEAR:
		mStepClear = 0.0f;
		if (mCntMove < mBestScore) {
			SaveScore();
		}
		break;
	case GameScene::STATE::CHANGE_STAGE:
		// だんだん暗くする
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		break;

	}

}

