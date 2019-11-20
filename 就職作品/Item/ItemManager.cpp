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
		if (TmpID != NUM_ITEM)		//�E����Ȃ�A�C�e����ID��Ԃ�
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
		if (TmpID != NUM_ITEM)		//�E����Ȃ�A�C�e����ID��Ԃ�
		{
			delete decoration[i];							//�C���X�^���X�폜
			decoration.erase(decoration.begin() + i);			//�z��폜
			i--;											//���������l�߂�
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
