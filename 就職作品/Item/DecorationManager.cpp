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

bool DecorationManager::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	for (auto *Decoration : decoration)
	{
		if (Decoration->CheckForCanPicUp(_Pos) == true)return true;		//�E����Ȃ�true��Ԃ�
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
