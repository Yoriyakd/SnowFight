#pragma once
#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_YellowBall :public DecorationBase {
public:
	Decoration_YellowBall(const D3DXVECTOR3 *_Pos);
	Decoration_YellowBall(const D3DXVECTOR3 * _Pos, ThrowingInitValue * ThrowingInitValue);
	~Decoration_YellowBall();
	void Draw();
private:
};
