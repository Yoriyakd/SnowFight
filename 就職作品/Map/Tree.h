#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Tree : public MapObj
{
public:
	Tree(D3DXVECTOR3 Pos, float Ang);		//置く座標を渡す
	~Tree();
};
