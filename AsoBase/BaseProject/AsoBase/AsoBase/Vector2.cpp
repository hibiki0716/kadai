#include"Vector2.h"

// コンストラクタ
Vector2::Vector2(){
	x = 0;
	y = 0;
}

// コンストラクタ
Vector2::Vector2(int vX, int vY){
	x = vX;
	y = vY;
}

Vector2 Vector2::Lerp(Vector2 start, Vector2 end, float t){
	// 線形補間
	Vector2 ret = start;
	ret.x += t * (end.x - start.x);
	ret.y += t * (end.y - start.y);

	return ret;
}
