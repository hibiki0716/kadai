#include<DxLib.h>
#include"PopupUIBase.h"
#include"KeyCheck.h"
#include "TopMenuUI.h"

void TopMenuUI::Init(void){
}

void TopMenuUI::Update(void){
	// ステージセレクトメニュー表示時には
	// Topメニューの矢印が移動しないように制御
	//PopupUIBase::Update();

	// Nキーが押された場合
	if (keyTrgDown[KEY_P1_A]) {

	}
}

void TopMenuUI::Draw(void){
}

void TopMenuUI::Release(void){
}
