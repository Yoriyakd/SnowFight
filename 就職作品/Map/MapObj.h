#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include<map>

enum MapOBJ_ID{BENCH, BOBBIN, TREE, X_MAS_TREE};

struct ObjData
{
	MeshName MeshID;
	MeshName CollisionMeshID;		//CollisionMeshName‚ªMeshName‚Æ“¯‚¶‚È‚çˆ—‚ğ”ò‚Î‚·(‘½•ª‚à‚Á‚Æ‚¢‚¢•û–@‚ª‚ ‚é)
	float ObjRadius;
	bool PossibleDecorate;
	CollisionDetectionType Type;			//”»’è‚Ì•û–@‚ğİ’è
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