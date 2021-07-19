#include<DxLib.h>
#include"KeyCheck.h"
#include"GameScene.h"
#include"PopupUIBase.h"
#include"StageSelectMenuUI.h"

void StageSelectMenuUI::Init(void){
}

void StageSelectMenuUI::Update(void){
	//PopupUIBase::Update();

	if (keyTrgDown[KEY_P1_A]) {
		// 選択されたステージへ遷移したい
		//mGameScene->ChangeSelectStage(mSelect+1);
		Close();
	}
}

void StageSelectMenuUI::Draw(void){
}

void StageSelectMenuUI::Close(void){
}
