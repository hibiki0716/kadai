#pragma once
#include "SceneManager.h"

class Application
{
public:
	bool Init(void);
	void Run(void);
	bool Release(void);
private:
	//�C���X�^���X�̐���
	SceneManager mSceneManager;
};