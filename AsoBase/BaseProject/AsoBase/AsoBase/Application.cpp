#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Application.h"

bool Application::Init(void){

	// システム処理
	SetWindowText("1916002_荒木響稀");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib の初期化失敗");
		return false;
	}

	KeyInit();	//キー情報の初期化
	mSceneManager.Init();

	// デバッグ
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	return true;

}

void Application::Run(void){
	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){
		
		_dbgStartDraw();

		CheckKeyList();	//キー情報の取得

		mSceneManager.Update();

		_dbgAddDraw();

		ScreenFlip();

	}
}

bool Application::Release(void){
	mSceneManager.Release();

	DxLib_End();

	return true;
}
