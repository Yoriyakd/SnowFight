#include "WavePattern1.h"
#include"GameScene.h"

WavePattern1::WavePattern1()
{
	nowWaveTime = 0;
	waveLimit = 10 * GameFPS;
}

WavePatternBase * WavePattern1::WaveProcessing(void)
{
	nowWaveTime++;

	if (nowWaveTime == 5 * GameFPS)
	{
		int EnemyCnt = 5;
		D3DXVECTOR3 SpownPoint;

		SpownPoint = D3DXVECTOR3(rand() % (int)stageBorder->Right, 0.0f, rand() % (int)stageBorder->Top);



		for (int i = 0; i < EnemyCnt; i++)
		{
			D3DXVECTOR3 Tmp;													//d‚È‚Á‚Ä‚È‚¢‚©‚Ìˆ—‚ð“ü‚ê‚é
			Tmp = D3DXVECTOR3(SpownPoint.x - (rand() % 5 - 15), 0, SpownPoint.z - (rand() % 5 - 15));
			enemyManager->SetEnemy(D3DXVECTOR3(Tmp));
		}
	}
	
	if (nowWaveTime >= waveLimit)
	{
		return new WavePattern1();
	}

	return nullptr;
}
