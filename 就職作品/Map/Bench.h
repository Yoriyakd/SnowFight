#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Bench : public MapObj
{
public:
	Bench(D3DXVECTOR3 Pos);		//置く座標を渡す
	~Bench();
	XFILE GetMesh();			//当たり判定用のメッシュを返す　オーバーライドしている
private:
	XFILE collisionMesh;		//当たり判定用のメッシュ
};
