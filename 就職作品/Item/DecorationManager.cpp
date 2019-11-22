#include "DecorationManager.h"

DecorationManager::DecorationManager()
{
}

DecorationManager::~DecorationManager()
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		delete decoration[i];
	}
	decoration.clear();
}

bool DecorationManager::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		if (decoration[i]->CheckForCanPicUp(_Pos) == true)		//拾えるならアイテムのIDを返す
		{
			return true;
		}
	}
	return false;
}

DecorationID DecorationManager::PickUp(const D3DXVECTOR3 * _Pos)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		if (decoration[i]->GetPicUpFlag() == true)		//拾えるならアイテムのIDを返す
		{
			DecorationID TmpID;
			TmpID = decoration[i]->GetID();
			delete decoration[i];							//インスタンス削除
			decoration.erase(decoration.begin() + i);			//配列削除
			i--;											//消した分詰める
			return TmpID;
		}
	}
	return NUM_ITEM;
}

void DecorationManager::Drop(const D3DXVECTOR3 * _Pos, DecorationID ID)			//この処理は重いみたい☆		新しく作っているから？プレイヤーのインベントリに入る=消えるからインスタンスを削除した
{
	switch (ID)
	{
	case RED_BALL:
		decoration.push_back(new Decoration_RedBall(_Pos));
		break;
	case BLUE_BALL:
		decoration.push_back(new Decoration_BlueBall(_Pos));
		break;
	case YELLOW_BALL:
		decoration.push_back(new Decoration_YellowBall(_Pos));
		break;
	default:
		break;
	}
	
}

void DecorationManager::Draw(void)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		decoration[i]->Draw();
	}
}

void DecorationManager::Updata(void)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		decoration[i]->Updata();
	}
}
