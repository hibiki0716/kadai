#pragma once
#include<vector>
#include<string>
#include"Vector2.h"
class GameScene;


class PopupUIBase
{
public:
	// 画面描画時の調整値
	static constexpr int MARGIN_CHOICE_X = 30;
	static constexpr int MARGIN_CHOICE_Y = 5;
	static constexpr int MARGIN_CHOICE_HEIGHT = 5;

	static constexpr int MARGIN_SELECT = 5;

	// コンストラクタ
	PopupUIBase(GameScene* scene);

	// オーバーライドする関数には頭に、virtualをつける
	virtual void Init(Vector2 pos);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	// メニューを開く
	void Open(void);
	//メニューを閉じる
	void Close(void);
	// メヌーが開いているか判断
	bool IsOpen(void);

private:
	GameScene* mGameScene;

	Vector2 mPos;
	Vector2 mSize;

	// メニューが開いているか
	bool mIsOpen;

	// メニューの選択
	std::vector<std::string>mChoices;

	// 選択No
	int mSelectNo;
};

