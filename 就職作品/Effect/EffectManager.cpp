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
}


void EffectManager::Update(void)
{
	billBoardMat = pPlayerCam->GetbillBoardMat();		//ビルボードの回転行列をセット

	for (unsigned int i = 0; i < snowFrag.size(); i++)
	{
		if (snowFrag[i]->Update() == false)	//falseが帰ってきたら削除
		{
			delete snowFrag[i];
			snowFrag.erase(snowFrag.begin() + i);
			i--;
		}
	}

	//アルファ値を下げて見えなくなったらインスタンス削除
	for (unsigned int i = 0; i < snowLocus.size(); i++)
	{
		snowLocus[i]->SetBillBoardMat(billBoardMat);
		if (snowLocus[i]->Update() == false)
		{
			delete snowLocus[i];
			snowLocus.erase(snowLocus.begin() + i);
			i--;
		}
	}
}

void EffectManager::SetPlayerCamPointer(PlayerCamera * PPlayerCam)
{
	pPlayerCam = PPlayerCam;
}
