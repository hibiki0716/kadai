#include<DxLib.h>
#include "GameCommon.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Storage.h"

Storage::Storage(GameScene* scene){
	mScene = scene;
	mManager = scene->GetSceneManager();
}

void Storage::Init(Vector2 mapPos){
	mImage = LoadGraph("Image/Storage.png", true);
	// マップ座標をスクリーン座標へ変換
	mPos = {
		mapPos.x * BLOCK_SIZE,
		mapPos.y * BLOCK_SIZE
	};

}

void Storage::Update(void){

}

void Storage::Draw(void){
	DrawGraph(GAME_AREA_X + mPos.x, GAME_AREA_Y + mPos.y,
		mImage,true);
}

void Storage::Release(void){
	DeleteGraph(mImage);
}

Vector2 Storage::GetPos(void)
{
	return mPos;
}
