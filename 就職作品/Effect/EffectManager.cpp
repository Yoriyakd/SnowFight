#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	AllDelete();
}

void EffectManager::AllDelete(void)
{
	for (auto *SnowFrag : snowFrag)
	{
		delete SnowFrag;
	}
	snowFrag.clear();

	for (auto *SnowLocus : snowLocus)
	{
		delete SnowLocus;
	}
	snowLocus.clear();
}

void EffectManager::NewSnowFrag(const D3DXVECTOR3 &Pos)
{
	snowFrag.push_back(new SnowFrag(Pos));
}

void EffectManager::NewSnowLocus(const D3DXMATRIX &SnowBallMat)
{
	snowLocus.push_back(new SnowLocus(SnowBallMat));
}

void EffectManager::Draw(void)
{
	for (auto *SnowFrag : snowFrag)
	{
		SnowFrag->Draw();
	}

	for (auto *SnowLocus : snowLocus)
	{
		SnowLocus->Draw();
	}
}


void EffectManager::Update(void)
{
	for (unsigned int i = 0; i < snowFrag.size(); i++)
	{
		snowFrag[i]->SetBillBoardMat(billBoardMat);		//�r���{�[�h�̉�]�s����Z�b�g
		if (snowFrag[i]->Update() == false)	//false���A���Ă�����폜
		{
			delete snowFrag[i];
			snowFrag.erase(snowFrag.begin() + i);	//�z��J��
			i--;									//���������߂�
		}
	}

	//�A���t�@�l�������Č����Ȃ��Ȃ�����C���X�^���X�폜
	for (unsigned int i = 0; i < snowLocus.size(); i++)
	{
		snowLocus[i]->SetBillBoardMat(billBoardMat);	//�r���{�[�h�̉�]�s����Z�b�g
		if (snowLocus[i]->Update() == false)
		{
			delete snowLocus[i];
			snowLocus.erase(snowLocus.begin() + i);	//�z��J��
			i--;									//���������߂�
		}
	}
}

void EffectManager::SetBillBoardMat(D3DXMATRIX * BillBoardMat)
{
	billBoardMat = *BillBoardMat;
}

