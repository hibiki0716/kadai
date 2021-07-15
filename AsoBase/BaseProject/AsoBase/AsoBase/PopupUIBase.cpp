#include<DxLib.h>
#include "PopupUIBase.h"

PopupUIBase::PopupUIBase(GameScene* scene){
	mGameScene = scene;
}

void PopupUIBase::Init(Vector2 pos){
	mIsOpen = false;
	mPos = pos;
	mSize = { 150,200 };
}

void PopupUIBase::Update(void){

}

void PopupUIBase::Draw(void){

	DrawBox(mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y, 0x000000, true);
	DrawBox(mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y, 0xffffff, false);
}

void PopupUIBase::Release(void){

}

void PopupUIBase::Open(void){
	mIsOpen = true;
}

void PopupUIBase::Close(void){
	mIsOpen = false;
}

bool PopupUIBase::IsOpen(void){
	return mIsOpen;
}
