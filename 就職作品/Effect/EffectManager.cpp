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

	for (auto *EnemyDeathAnime : enemyDeathAnime)
	{
		delete EnemyDeathAnime;
	}
	enemyDeathAnime.clear();
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

	for (auto *EnemyDeathAnime : enemyDeathAnime)
	{
		EnemyDeathAnime->Draw();
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

	//�Đ������I���ƃC���X�^���X�폜
	for (unsigned int i = 0; i < enemyDeathAnime.size(); i++)
	{
		if (enemyDeathAnime[i]->Update() == false)
		{
			delete enemyDeathAnime[i];
			enemyDeathAnime.erase(enemyDeathAnime.begin() + i);	//�z��J��
			i--;									//���������߂�

		}
	}
}

void EffectManager::SetBillBoardMat(D3DXMATRIX * BillBoardMat)
{
	billBoardMat = *BillBoardMat;
}

