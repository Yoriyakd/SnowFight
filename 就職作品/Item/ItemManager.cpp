#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		delete decoration[i];
	}
	decoration.clear();
}

bool ItemManager::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		DecorationID TmpID;
		TmpID = decoration[i]->CheckForCanPicUp(_Pos);
		if (TmpID != NUM_ITEM)		//拾えるならアイテムのIDを返す
		{
			return true;
		}
	}
	return false;
}

DecorationID ItemManager::PickUpItem(const D3DXVECTOR3 * _Pos)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		DecorationID TmpID;
		TmpID = decoration[i]->CheckForCanPicUp(_Pos);
		if (TmpID != NUM_ITEM)		//拾えるならアイテムのIDを返す
		{
			delete decoration[i];							//インスタンス削除
			decoration.erase(decoration.begin() + i);			//配列削除
			i--;											//消した分詰める
			return TmpID;
		}
		return NUM_ITEM;
	}
}

void ItemManager::Draw(void)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		decoration[i]->Draw();
	}
}

void ItemManager::Updata(void)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		decoration[i]->Updata();
	}
}
