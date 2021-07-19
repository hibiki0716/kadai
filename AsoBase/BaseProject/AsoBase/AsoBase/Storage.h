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

	// ���W�̎擾
	Vector2 GetPos(void);

private:

	SceneManager* mManager;
	GameScene* mScene;

	int mImage;

	// �X�N���[�����W
	Vector2 mPos;
};

