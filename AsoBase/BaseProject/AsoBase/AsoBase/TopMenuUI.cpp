#include<DxLib.h>
#include"PopupUIBase.h"
#include"KeyCheck.h"
#include"PopupUIBase.h"
#include"HightScoreMenuUI.h"
#include"TopMenuUI.h"

void TopMenuUI::Init(void){
	// ハイスコア描画
	/*mHightScoreMenuUI = new HightScoreMenuUI(mGameScene);
	mHightScoreMenuUI->Init({ x,y });*/
}

void TopMenuUI::Update(void){
	// ステージセレクトメニュー表示時には
	// Topメニューの矢印が移動しないように制御
	//bool isOpen = mStageSelectMenuUI->IsOpen();
	/*if (isOpen == false) {
		isOpen = mHightScoreMenuUI -> IsOpen();
	}*/
	//if (isOpen) {
	/*if (mStageSelectMenuUI->IsOpen()) {

	}*/
	//	mStageSelectMenuUI->Update();
	//}
	//else {

	//	PopupUIBase::Update();

	//	// Nキーが押された場合
	//	if (keyTrgDown[KEY_P1_A]) {
	/*switch (mSelectNo)
	{
	case 0:
		mStageSelectMenuUI->Open();
		break:

	case 1:
		mStageSelectMenuUI->Open();
		break:
	}*/
	//	}
	//}

}

void TopMenuUI::Draw(void){

}

void TopMenuUI::Release(void){
}
