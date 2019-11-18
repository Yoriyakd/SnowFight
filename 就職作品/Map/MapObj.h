#pragma once
#include"../main.h"
class MapObj{
public:
	MapObj();
	~MapObj();
	virtual void Draw();
	D3DXMATRIX GetMat();
	D3DXVECTOR3 GetPos();
	virtual XFILE GetMesh();
	CollisionDetectionType GetCollisionDetectionType();
	virtual float GetRadius();
protected:
	XFILE mesh;
	D3DXMATRIX mat;
	D3DXVECTOR3 pos;
	CollisionDetectionType type;			//”»’è‚Ì•û–@‚ğİ’è
	float objRadius;
};