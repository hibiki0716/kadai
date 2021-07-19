#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager){
}

void TitleScene::Init(void){
	//�^�C�g���摜�̓ǂݍ���
	mImage = LoadGraph("Image/Scene/Title.png");

	count = 0;
}

void TitleScene::Update(void){

	if (keyTrgDown[KEY_SYS_START]){
		mSceneManager->ChangeScene(SCENE_ID::GAME, true);
	}

}

void TitleScene::Draw(void){
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// �^�C�g���摜�̕`��
	DrawGraph(0, 0, mImage, true);

	SetFontSize(50);
	ChangeFont("Stencil Std");
	//Bodoni MT//Comic Sans MS//Forte
	
	count++;
	if (count /30 % 2) {
		DrawString(DEFAULT_SCREEN_SIZE_X / 2 + 40, DEFAULT_SCREEN_SIZE_Y, "SPEACE KEY", 0x999999);

	}
		
}

void TitleScene::Release(void){
	// �摜�̊J��
	DeleteGraph(mImage);
}
