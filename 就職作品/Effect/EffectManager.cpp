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
	billBoardMat = pPlayerCam->GetbillBoardMat();		//ビルボードの回転行列をセット

	for (unsigned int i = 0; i < snowFrag.size(); i++)
	{
		snowFrag[i]->SetBillBoardMat(billBoardMat);		//ビルボードの回転行列をセット
		if (snowFrag[i]->Update() == false)	//falseが帰ってきたら削除
		{
			delete snowFrag[i];
			snowFrag.erase(snowFrag.begin() + i);	//配列開放
			i--;									//消した分つめる
		}
	}

	//アルファ値を下げて見えなくなったらインスタンス削除
	for (unsigned int i = 0; i < snowLocus.size(); i++)
	{
		snowLocus[i]->SetBillBoardMat(billBoardMat);	//ビルボードの回転行列をセット
		if (snowLocus[i]->Update() == false)
		{
			delete snowLocus[i];
			snowLocus.erase(snowLocus.begin() + i);	//配列開放
			i--;									//消した分つめる
		}
	}

	//再生をし終わるとインスタンス削除
	for (unsigned int i = 0; i < enemyDeathAnime.size(); i++)
	{
		if (enemyDeathAnime[i]->Update() == false)
		{
			delete enemyDeathAnime[i];
			enemyDeathAnime.erase(enemyDeathAnime.begin() + i);	//配列開放
			i--;									//消した分つめる

		}
	}
}

void EffectManager::SetPlayerCamPointer(PlayerCamera * PPlayerCam)
{
	pPlayerCam = PPlayerCam;
}
