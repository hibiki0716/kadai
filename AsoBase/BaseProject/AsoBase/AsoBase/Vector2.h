#pragma once
class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2();

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// ���`���
	// �����i�J�n���W�A�I�����W�A�����i0.0���`1.0���j
	static Vector2 Lerp(Vector2 start, Vector2 end, float t);
};

