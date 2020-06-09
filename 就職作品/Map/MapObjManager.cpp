#include "MapObjManager.h"

MapObjManager::MapObjManager()
{
}

MapObjManager::~MapObjManager()
{
	for (unsigned int i = 0; i < mapObj.size(); i++)
	{
		delete mapObj[i];
	}
	mapObj.clear();
}


void MapObjManager::SetTree(D3DXVECTOR3 Pos, float Ang)
{
	mapObj.push_back(new Tree(Pos, Ang));
}

void MapObjManager::SetBench(D3DXVECTOR3 Pos, float Ang)
{
	mapObj.push_back(new Bench(Pos, Ang));
}

void MapObjManager::SetBobbin_Red(D3DXVECTOR3 Pos, float Ang)
{
	mapObj.push_back(new Bobbin_Red(Pos, Ang));
}

void MapObjManager::SetXmasTree(D3DXVECTOR3 Pos)
{
	mapObj.push_back(new XmasTree(Pos));
}

D3DXVECTOR3 MapObjManager::GetXmasTreePos(void)
{
	for (unsigned int i = 0; i < mapObj.size(); i++)
	{
		if (mapObj[i]->GetPossibleDecorate() == true)			//飾れるオブジェの座標を返す
		{
			return mapObj[i]->GetPos();
		}
	}
	return D3DXVECTOR3(0, 0, 0);		//エラー
}

void MapObjManager::Draw()
{
	for (unsigned int i = 0; i < mapObj.size(); i++)
	{
		mapObj[i]->Draw();
	}
}

void MapObjManager::Update()
{
}
