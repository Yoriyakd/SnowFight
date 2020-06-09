#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include<map>

enum MapOBJ_ID{BENCH, BOBBIN, TREE, X_MAS_TREE};

struct ObjData
{
	MeshName MeshID;
	MeshName CollisionMeshID;		//CollisionMeshName��MeshName�Ɠ����Ȃ珈�����΂�(���������Ƃ������@������)
	float ObjRadius;
	bool PossibleDecorate;
	CollisionDetectionType Type;			//����̕��@��ݒ�
};

class MapObj{
public:
	MapObj();
	~MapObj();
	void CreatObj(D3DXVECTOR3 Pos, float Ang, MapOBJ_ID _ID);
	virtual void Draw();
	D3DXMATRIX GetMat();
	D3DXVECTOR3 GetPos();
	virtual XFILE GetMesh();
	CollisionDetectionType GetCollisionDetectionType();
	virtual float GetRadius();
	bool GetPossibleDecorate();
protected:
	XFILE mesh;
	XFILE* collisionMesh;
	D3DXMATRIX mat;
	D3DXVECTOR3 pos;

	MapOBJ_ID ID;

	static std::map<MapOBJ_ID ,ObjData> ObjDataList;
};