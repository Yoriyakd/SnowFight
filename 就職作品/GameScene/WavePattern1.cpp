#include "WavePattern1.h"
#include"GameScene.h"

WavePattern1::WavePattern1()
{
	nowWaveTime = 0;
	waveLimit = 30 * GameFPS;
}

WavePatternBase * WavePattern1::WaveProcessing(void)
{
	nowWaveTime++;

	if (nowWaveTime % 100 == 0)
	{
		int EnemyCnt = 5;
		D3DXVECTOR3 SpownPoint;

		//SpownPoint = D3DXVECTOR3(rand() % (int)stageSizeX, 0.0f, rand() % (int)stageSizeZ);



		for (int i = 0; i < EnemyCnt; i++)
		{
			D3DXVECTOR3 Tmp;													//d‚È‚Á‚Ä‚È‚¢‚©‚Ìˆ—‚ð“ü‚ê‚é
			Tmp = D3DXVECTOR3(SpownPoint.x - (rand() % 5 - 15), 0, SpownPoint.z - (rand() % 5 - 15));
			enemyManager->SetEnemy(D3DXVECTOR3(Tmp));
		}
	}
	
	return nullptr;
}
