#include "MapObj.h"
#include"../DirectX/Direct3D.h"

std::map<MapOBJ_ID, ObjData> MapObj::ObjDataList
{
	{BENCH, ObjData{Bench_M, BenchCollision_M, 5.5f, false, Ray}},
	{BOBBIN, ObjData{Bobbin_Red_M, Bobbin_Red_M, 4.0f, false, Circles}},
	{TREE, ObjData{Tree_M, Tree_M, 2.5f, false, Circles}},
	{X_MAS_TREE, ObjData{XmasTree_M, XmasTree_M, 14.0f, true, Circles}},
};

MapObj::MapObj()
{
	ObjDataList;
}

MapObj::~MapObj()
{
}

void MapObj::CreatObj(D3DXVECTOR3 Pos, float Ang, MapOBJ_ID _ID)
{
	ID = _ID;
	mesh = GetResource.GetXFILE(ObjDataList[_ID].MeshID);

	if (ObjDataList[_ID].MeshID != ObjDataList[_ID].CollisionMeshID)
	{
		collisionMesh = new XFILE;
		*collisionMesh = GetResource.GetXFILE(ObjDataList[_ID].CollisionMeshID);		//MeshIDとCollisionMeshIDがが違うかったら判定用のメッシュを用意する振る舞いが複数あるから多分悪い設計要修正
	}
	else
	{
		collisionMesh = nullptr;
	}

	pos = Pos;

	D3DXMATRIX TmpRotMatY, TmpTransMat;
	D3DXMatrixRotationY(&TmpRotMatY, D3DXToRadian(Ang));

	D3DXMatrixTranslation(&TmpTransMat, Pos.x, Pos.y, Pos.z);

	mat = TmpRotMatY * TmpTransMat;
}

void MapObj::Draw()
{
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

D3DXMATRIX MapObj::GetMat()
{
	return mat;
}

D3DXVECTOR3 MapObj::GetPos()
{
	return pos;
}

XFILE MapObj::GetMesh()
{
	if (collisionMesh != nullptr)
	{
		return *collisionMesh;
	}
	return mesh;
}

CollisionDetectionType MapObj::GetCollisionDetectionType(void)
{
	return ObjDataList[ID].Type;
}

float MapObj::GetRadius()
{
	return ObjDataList[ID].ObjRadius;
}

bool MapObj::GetPossibleDecorate()
{
	return ObjDataList[ID].PossibleDecorate;
}
