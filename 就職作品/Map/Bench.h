#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Bench : public MapObj
{
private:
	D3DXVECTOR3 pos;
	XFILE collisionMesh;		//当たり判定用のメッシュ
public:
	Bench(D3DXVECTOR3 Pos);		//置く座標を渡す
	~Bench();
	XFILE GetMesh();			//当たり判定用のメッシュを返す　オーバーライドしている
};
