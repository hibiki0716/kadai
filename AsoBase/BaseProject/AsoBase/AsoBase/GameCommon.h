#pragma once

// �X�N���[���T�C�Y
#define SCREEN_SIZE_X 1024
#define SCREEN_SIZE_Y 640

// �Q�[���G���A
#define GAME_AREA_X 32
#define GAME_AREA_Y 64

// �}�b�v�T�C�Y
#define MAP_SIZE_X 30
#define MAP_SIZE_Y 17

// �u���b�N�T�C�Y
#define BLOCK_SIZE 32

// �X�e�[�W�t�@�C��
#define FILE_PATH_CSV "StageData/Stage"
#define FILE_NAME_GIMMICK "GimmickChip.csv"
#define FILE_NAME_GROUND "GroundChip.csv"
#define FILE_NAME_SCORE "Score.csv"

// ����
enum class DIR
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
	MAX
};
