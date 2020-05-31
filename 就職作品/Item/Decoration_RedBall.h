#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_RedBall: public DecorationBase {
public:
	Decoration_RedBall(const D3DXVECTOR3 *_Pos);
	Decoration_RedBall(const ThrowingInitValue * ThrowingInitValue);
	~Decoration_RedBall();
private:
};
