#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Bobbin_Red : public MapObj
{
public:
	Bobbin_Red(D3DXVECTOR3 Pos, float Ang);		//置く座標回転を渡す
	~Bobbin_Red();
private:
};