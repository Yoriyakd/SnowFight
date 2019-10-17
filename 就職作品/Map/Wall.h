#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include"../map/MapObj.h"

class Wall : public MapObj{
private:
	D3DXVECTOR3 pos;
public:
	Wall(D3DXVECTOR3 Pos);		//’u‚­À•W‚ğ“n‚·
	~Wall();
};
