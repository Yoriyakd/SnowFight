#pragma once
#include<vector>
#include"MapObj.h"
#include"Wall.h"
#include"Tree.h"

class MapObjManager {
private:
public:
	std::vector<MapObj*> mapObj;

	MapObjManager();
	~MapObjManager();

	void SetWall(D3DXVECTOR3 Pos);
	void SetTree(D3DXVECTOR3 Pos);

	void Draw();
	void Update();
};
