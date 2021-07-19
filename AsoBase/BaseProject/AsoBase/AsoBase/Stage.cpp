#include<DxLib.h>
#include<string>
#include<vector>
#include<fstream>
#include"GameScene.h"
#include"Utility.h"
#include"Stage.h"

Stage::Stage(GameScene* scene){
	mGameScene = scene;
	//scene->Init();
}

void Stage::Init(int StageNo){
	LoadDivGraph("Image/StageChip.png", 4, 2, 2,
		BLOCK_SIZE, BLOCK_SIZE,
		&mImage[0],true);

	mImageOutFloor = mImage[0];
	mImageInFloor = mImage[1];
	mImageInWall = mImage[2];
	mImageOutWall = mImage[3];

	// �R�[�h
	//SetStage(StageNo);

	// �O���f�[�^���g�p���āA�X�e�[�W��ݒ�
	LoadData(StageNo);

}

void Stage::Update(void){

}

void Stage::Draw(void) {

	int mapNo;
	int tmpImage = -1;

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			mapNo = mMap[y][x];
			switch (mapNo)
			{
			case -1:
				tmpImage = mImageOutFloor;
				break;
			case 1:
				tmpImage = mImageInFloor;
				break;
			case 2:
				tmpImage = mImageInWall;
				break;
			default:
				break;
			}
			DrawGraph(GAME_AREA_X +( x * BLOCK_SIZE)
				, GAME_AREA_Y + (y * BLOCK_SIZE)
				, tmpImage, true);
		}
	}

	// �Q�[���G���A�O���̕`��
	int scSizeX = SCREEN_SIZE_X / BLOCK_SIZE;
	int scSizeY = SCREEN_SIZE_Y / BLOCK_SIZE;

	// ��
	for(int x = 0; x < scSizeX; x++) {
		DrawGraph(x * BLOCK_SIZE, 0 * BLOCK_SIZE, mImageOutWall, true);
		DrawGraph(x * BLOCK_SIZE, 1 * BLOCK_SIZE, mImageOutWall, true);
		DrawGraph(x * BLOCK_SIZE, (scSizeY-1) * BLOCK_SIZE, mImageOutWall, true);
	}
	// �c
	for (int y = 0; y < scSizeY; y++) {
		DrawGraph(0 * BLOCK_SIZE, y * BLOCK_SIZE, mImageOutWall, true);
		DrawGraph((scSizeX-1) * BLOCK_SIZE, y * BLOCK_SIZE, mImageOutWall, true);
	}
}

void Stage::Release(void){
	DeleteGraph(mImageInWall);
	DeleteGraph(mImageInFloor);
	DeleteGraph(mImageOutWall);
	DeleteGraph(mImageOutFloor);
}

bool Stage::IsCollositiom(Vector2 mapPos){

	if (mapPos.y < 0) {
		return true;
	}
	if (mapPos.y >= (MAP_SIZE_Y - 1)) {
		return true;
	}

	return mMap[mapPos.y][mapPos.x] > 1;
}

void Stage::SetStage(int StageNo)
{

	switch (StageNo)
	{
	case 2: {
		int tmpMap[MAP_SIZE_Y][MAP_SIZE_X] = {
			{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,9,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 1,1,1,9,9,9,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,9,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,9,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,9, 1,1,1,1,1,1,1,1,1,1, 9,0,0,0,0,0,0,0,0,0},

		{0,0,0,0,0,0,0,0,0,9, 9,9,9,9,9,9,9,9,9,9, 9,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0},
		};

		for (int y = 0; y < MAP_SIZE_Y; y++) {
			for (int x = 0; x < MAP_SIZE_X; x++) {
				mMap[y][x] = tmpMap[y][x];
			}
		}
	}
	}
}

void Stage::LoadData(int StageNo){
	// �t�@�C���p�X
	std::string filePath = mGameScene->GetCsvPathGround(StageNo);
	// �t�@�C����ǂݍ���
	std::ifstream ifs(filePath);
	// 1�s���ǂݍ���
	int y = 0;
	std::string line;

	while (getline(ifs, line)) {

		// Y�ŕ������ꂽline
		std::vector<std::string> strvec = Utility::Split(line, ',');

		// X�ŕ������ꂽstrvec

		// mMap�ɒl�������āA
		// �X�e�[�W���쐬
		for (int x = 0; x < strvec.size(); x++) {
			mMap[y][x] = stoi(strvec[x]);
		}
		int i = stoi(strvec[0]);

		y++;
	}

	if (true){}
}
