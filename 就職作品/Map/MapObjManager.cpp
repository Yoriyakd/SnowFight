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

void MapObjManager::CreatObj(D3DXVECTOR3 Pos, float Ang, MapOBJ_ID ID)
{
	mapObj.push_back(new MapObj());
	mapObj.back()->CreatObj(Pos, Ang, ID);
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

