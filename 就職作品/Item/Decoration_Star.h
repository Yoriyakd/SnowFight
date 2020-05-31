#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_Star : public DecorationBase{
public:
	Decoration_Star(const D3DXVECTOR3 *_Pos);
	Decoration_Star(const ThrowingInitValue * ThrowingInitValue);
	~Decoration_Star();
private:
};