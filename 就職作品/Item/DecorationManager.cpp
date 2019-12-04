#include "DecorationManager.h"

DecorationManager::DecorationManager()
{
	resourceManager->GetXFILE("Decoration_RedBall.x");			//1�x�ǂݍ���ł���(�Q�[�����̕��׌y��)
	resourceManager->GetXFILE("Decoration_BlueBall.x");
	resourceManager->GetXFILE("Decoration_YellowBall.x");
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
