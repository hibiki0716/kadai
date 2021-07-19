#include "DxLib.h"
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "GameoverScene.h"

GameoverScene::GameoverScene(SceneManager* manager) : SceneBase(manager){
}

void GameoverScene::Init(void){
	//タイトル画像の読み込み
	mImage = LoadGraph("Image/Scene/End.png");

	count = 0;
}

void GameoverScene::Update(void){

	if (keyTrgDown[KEY_SYS_START]){
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

}

void GameoverScene::Draw(){

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// 画像の描画
	DrawGraph(0, 0, mImage, true);

	SetFontSize(50);

	count++;
	if (count / 30 % 2) {
		DrawString(DEFAULT_SCREEN_SIZE_X / 2 + 40, DEFAULT_SCREEN_SIZE_Y, "SPEACE KEY", 0x999999);

	}

}

void GameoverScene::Release(void){
	// 画像の開放
	DeleteGraph(mImage);
}
