#include "DecorationManager.h"

DecorationManager::DecorationManager()
{
	GetResource.GetXFILE(Decoration_RedBall_M);			//1�x�ǂݍ���ł���(�Q�[�����̕��׌y��)
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
		if (decoration[i]->GetDecoratedState() == false)			//�����Ă��Ȃ����̂��폜����
		{
			delete decoration[i];
			decoration.erase(decoration.begin() + i);			//�z��폜
			i--;											//���������l�߂�
		}
	}
}

void DecorationManager::NewDecoration(D3DXVECTOR3 *_Pos, CarryObjectID ID)
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

bool DecorationManager::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	for (auto *Decoration : decoration)
	{
		if (Decoration->CheckForCanPicUp(_Pos) == true)return true;		//�E����Ȃ�true��Ԃ�
	}
	return false;
}

CarryObjectID DecorationManager::PickUp(const D3DXVECTOR3 * _Pos)
{
	for (unsigned int i = 0; i < decoration.size(); i++)
	{
		if (decoration[i]->GetPicUpFlag() == true)		//�E����Ȃ�A�C�e����ID��Ԃ�
		{
			CarryObjectID TmpID;
			TmpID = decoration[i]->GetID();
			delete decoration[i];							//�C���X�^���X�폜
			decoration.erase(decoration.begin() + i);			//�z��폜
			i--;											//���������l�߂�
			return TmpID;
		}
	}
	return NUM_ITEM_Dummy;			
}

void DecorationManager::Throw(CarryObjectID ID, ThrowingInitValue * ThrowingInitValue)
{
	switch (ID)
	{
	case RED_BALL:
		decoration.push_back(new Decoration_RedBall(ThrowingInitValue));
		break;
	case BLUE_BALL:
		decoration.push_back(new Decoration_BlueBall(ThrowingInitValue));
		break;
	case YELLOW_BALL:
		decoration.push_back(new Decoration_YellowBall(ThrowingInitValue));
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
