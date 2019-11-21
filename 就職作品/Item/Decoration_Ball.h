#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_Ball:public DecorationBase {
public:
	Decoration_Ball(const D3DXVECTOR3 *_Pos, DecorationID ID);
	~Decoration_Ball();
	void Draw();
private:
	D3DCOLORVALUE color;
};
