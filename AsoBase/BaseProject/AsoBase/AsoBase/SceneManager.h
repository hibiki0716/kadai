//#pragma once
#include "TitleScene.h"
class SceneBase;
class Fader;

// �V�[���Ǘ��p
enum class SCENE_ID
{
	NONE
	, TITLE
	, GAME
	, GAMEOVER
};

class SceneManager
{

public:

	void Init(void);
	void Update(void);
	void Release(void);

	void ChangeScene(SCENE_ID nextId, bool isFading);
	
	// �f���^�^�C���̎擾
	float GetDeltaTime(void);

private:

	SCENE_ID mSceneID;
	SCENE_ID mWaitSceneID;

	SceneBase* mScene;
	Fader* mFader;

	bool mIsSceneChanging;

	// �f���^�^�C��
	float mTickCnt;
	float mDeltaTiime;

	void DoChangeScene(void);

	
};