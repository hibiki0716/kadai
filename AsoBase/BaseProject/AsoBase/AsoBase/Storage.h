#pragma once
#include"Vector2.h"

class SceneManager;
class GameScene;

class Storage
{
public:

	Storage(GameScene* scene);
	void Init(Vector2 mapPos);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 座標の取得
	Vector2 GetPos(void);

private:

	SceneManager* mManager;
	GameScene* mScene;

	int mImage;

	// スクリーン座標
	Vector2 mPos;
};

