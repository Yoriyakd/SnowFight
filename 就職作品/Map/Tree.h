#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Tree : public MapObj
{
private:
	D3DXVECTOR3 pos;
public:
	Tree(D3DXVECTOR3 Pos);		//置く座標を渡す
	~Tree();
};


