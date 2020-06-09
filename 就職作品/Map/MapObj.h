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
	bool GetPossibleDecorate();
protected:
	XFILE mesh;
	D3DXMATRIX mat;
	D3DXVECTOR3 pos;
	CollisionDetectionType type;			//����̕��@��ݒ�
	float objRadius;
	bool possibleDecorate;			//�f�R���[�V���������邱�Ƃ��ł��邩
};