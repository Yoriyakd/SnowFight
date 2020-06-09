#pragma once
#include<vector>
//#include"MapObj.h"
//#include"Tree.h"
//#include"Bench.h"
//#include"XmasTree.h"
//#include"Bobbin_Red.h"
#include"MapObj.h"

class MapObjManager {
public:
	std::vector<MapObj*> mapObj;

	MapObjManager();
	~MapObjManager();

	void CreatObj(D3DXVECTOR3 Pos, float Ang, MapOBJ_ID ID);
	D3DXVECTOR3 GetXmasTreePos(void);

	void Draw();
};
