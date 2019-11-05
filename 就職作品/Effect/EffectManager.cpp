#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
	for (unsigned int i = 0; i < snowFrag.size(); i++)
	{
		delete snowFrag[i];
	}
	snowFrag.clear();

	for (unsigned int i = 0; i < snowLocus.size(); i++)
	{
		delete snowLocus[i];
	}
	snowLocus.clear();

	for (unsigned int i = 0; i < enemyDeathAnime.size(); i++)
	{
		delete enemyDeathAnime[i];
	}
	enemyDeathAnime.clear();
}

void EffectManager::Draw(void)
{
	for (unsigned int i = 0; i < snowFrag.size(); i++)
	{
		snowFrag[i]->Draw();
	}

	for (unsigned int i = 0; i < snowLocus.size(); i++)
	{
		snowLocus[i]->Draw();
	}

	for (unsigned int i = 0; i < enemyDeathAnime.size(); i++)
	{
		enemyDeathAnime[i]->Draw();
	}
}


void EffectManager::Update(void)
{
	billBoardMat = pPlayerCam->GetbillBoardMat();		//�r���{�[�h�̉�]�s����Z�b�g

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

void EffectManager::SetPlayerCamPointer(PlayerCamera * PPlayerCam)
{
	pPlayerCam = PPlayerCam;
}
