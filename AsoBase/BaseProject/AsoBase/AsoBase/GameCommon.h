#pragma once

// スクリーンサイズ
#define SCREEN_SIZE_X 1024
#define SCREEN_SIZE_Y 640

// ゲームエリア
#define GAME_AREA_X 32
#define GAME_AREA_Y 64

// マップサイズ
#define MAP_SIZE_X 30
#define MAP_SIZE_Y 17

// ブロックサイズ
#define BLOCK_SIZE 32

// ステージファイル
#define FILE_PATH_CSV "StageData/Stage"
#define FILE_NAME_GIMMICK "GimmickChip.csv"
#define FILE_NAME_GROUND "GroundChip.csv"
#define FILE_NAME_SCORE "Score.csv"

// 方向
enum class DIR
{
	DOWN,
	LEFT,
	RIGHT,
	UP,
	MAX
};
