#pragma once
#include<vector>
#include<string>
#include"Vector2.h"
class GameScene;


class PopupUIBase
{
public:
	// ��ʕ`�掞�̒����l
	static constexpr int MARGIN_CHOICE_X = 30;
	static constexpr int MARGIN_CHOICE_Y = 5;
	static constexpr int MARGIN_CHOICE_HEIGHT = 5;

	static constexpr int MARGIN_SELECT = 5;

	// �R���X�g���N�^
	PopupUIBase(GameScene* scene);

	// �I�[�o�[���C�h����֐��ɂ͓��ɁAvirtual������
	virtual void Init(Vector2 pos);
	virtual void Update(void);
	virtual void Draw(void);
	void Release(void);

	// ���j���[���J��
	void Open(void);
	//���j���[�����
	void Close(void);
	// ���k�[���J���Ă��邩���f
	bool IsOpen(void);

private:
	GameScene* mGameScene;

	Vector2 mPos;
	Vector2 mSize;

	// ���j���[���J���Ă��邩
	bool mIsOpen;

	// ���j���[�̑I��
	std::vector<std::string>mChoices;

	// �I��No
	int mSelectNo;
};

