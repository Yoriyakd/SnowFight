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

void EffectManager::SetBillBoardMat(D3DXMATRIX * BillBoardMat)
{
	billBoardMat = *BillBoardMat;
}

