#pragma once
#include"DecorationBase.h"
#include"../ResourceManager.h"
class Decoration_BlueBall :public DecorationBase {
public:
	Decoration_BlueBall(const D3DXVECTOR3 *_Pos);
	~Decoration_BlueBall();
	void Draw();
private:
};
