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
		if (decoration[i]->CheckForCanPicUp(_Pos) == true)		//�E����Ȃ�A�C�e����ID��Ԃ�
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
		if (decoration[i]->GetPicUpFlag() == true)		//�E����Ȃ�A�C�e����ID��Ԃ�
		{
			DecorationID TmpID;
			TmpID = decoration[i]->GetID();
			delete decoration[i];							//�C���X�^���X�폜
			decoration.erase(decoration.begin() + i);			//�z��폜
			i--;											//���������l�߂�
			return TmpID;
		}
	}
	return NUM_ITEM;
}

void DecorationManager::Drop(const D3DXVECTOR3 * _Pos, DecorationID ID)
{
	switch (ID)
	{
	case RED_BALL:
		decoration.push_back(new Decoration_Ball(_Pos, ID));
		break;
	case BLUE_BALL:
		decoration.push_back(new Decoration_Ball(_Pos, ID));
		break;
	case GREEN_BALL:
		decoration.push_back(new Decoration_Ball(_Pos, ID));
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
