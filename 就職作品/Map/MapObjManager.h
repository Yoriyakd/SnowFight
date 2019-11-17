#pragma once
#include<vector>
#include"MapObj.h"
#include"Tree.h"
#include"Bench.h"

class MapObjManager {
private:
public:
	std::vector<MapObj*> mapObj;

	MapObjManager();
	~MapObjManager();

	void SetTree(D3DXVECTOR3 Pos);
	void SetBench(D3DXVECTOR3 Pos);

	void Draw();
	void Update();
};
