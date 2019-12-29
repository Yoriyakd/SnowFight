#include "DecorationManager.h"

DecorationManager::DecorationManager()
{
	GetResource.GetXFILE(Decoration_RedBall_M);			//1度読み込んでおく(ゲーム中の負荷軽減)
	GetResource.GetXFILE(Decoration_BlueBall_M);
	GetResource.GetXFILE(Decoration_YellowBall_M);
}

DecorationManager::~DecorationManager()
{
	for (auto *Decoration : decoration)
	{
		delete Decoration;
	}
	decoration.clear();
}

void DecorationManager::DeleteToResult(void)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		if (decoration[i]->GetDecoratedState() == false)			//飾られていないものを削除する
		{
			delete decoration[i];
			decoration.erase(decoration.begin() + i);			//配列削除
			i--;											//消した分詰める
		}
	}
}

bool DecorationManager::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	for (auto *Decoration : decoration)
	{
		if (Decoration->CheckForCanPicUp(_Pos) == true)return true;		//拾えるならtrueを返す
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

void DecorationManager::Throw(const D3DXVECTOR3 * _Pos, DecorationID ID, ThrowingInitValue * ThrowingInitValue)
{
	switch (ID)
	{
	case RED_BALL:
		decoration.push_back(new Decoration_RedBall(_Pos, ThrowingInitValue));
		break;
	case BLUE_BALL:
		decoration.push_back(new Decoration_BlueBall(_Pos, ThrowingInitValue));
		break;
	case YELLOW_BALL:
		decoration.push_back(new Decoration_YellowBall(_Pos, ThrowingInitValue));
		break;
	default:
		break;
	}
	
}

void DecorationManager::Draw(void)
{
	for (auto *Decoration : decoration)
	{
		Decoration->Draw();
	}
}

void DecorationManager::Updata(void)
{
	for (auto *Decoration : decoration)
	{
		Decoration->Updata();
	}
}
