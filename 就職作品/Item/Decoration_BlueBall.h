#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_BlueBall :public DecorationBase {
public:
	Decoration_BlueBall(const D3DXVECTOR3 *_Pos);
	Decoration_BlueBall(const ThrowingInitValue * ThrowingInitValue);
	~Decoration_BlueBall();
protected:
	float GetCanPicUpRange();
private:
	static const float BLUE_PIC_UP_RANGE;
};
