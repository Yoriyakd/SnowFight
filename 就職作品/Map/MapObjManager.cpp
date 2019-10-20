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

void MapObjManager::SetWall(D3DXVECTOR3 Pos)
{
	mapObj.push_back(new Wall(Pos));
}

void MapObjManager::SetTree(D3DXVECTOR3 Pos)
{
	mapObj.push_back(new Tree(Pos));
}

void MapObjManager::SetBench(D3DXVECTOR3 Pos)
{
	mapObj.push_back(new Bench(Pos));
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
	for (unsigned int i = 0; i < mapObj.size(); i++)
	{
		mapObj[i]->Draw();
	}
}
