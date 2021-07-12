#pragma once
class Vector2
{
public:

	int x;
	int y;

	// コンストラクタ
	Vector2();

	// コンストラクタ
	Vector2(int vX, int vY);

	// 線形補間
	// 引数（開始座標、終了座標、割合（0.0ｆ～1.0ｆ）
	static Vector2 Lerp(Vector2 start, Vector2 end, float t);
};

