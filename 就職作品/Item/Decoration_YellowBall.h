#pragma once
#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_YellowBall :public DecorationBase {
public:
	Decoration_YellowBall(const D3DXVECTOR3 *_Pos);
	Decoration_YellowBall(const ThrowingInitValue *ThrowingInitValue);
	~Decoration_YellowBall();
protected:
	float GetCanPicUpRange();
private:
	const static float YELLOW_PIC_UP_RANGE;
};
