#include "WavePattern1.h"
#include"GameScene.h"

WavePatternRandom::WavePatternRandom()
{
	nowWaveTime = 0;
	waveLimit = 5 * GameFPS;
}

WavePatternBase * WavePatternRandom::WaveProcessing(EnemyManager & EnemyManager, DecorationManager & DecorationManager, StageBorder & StageBorder)
{
	nowWaveTime++;

	if (nowWaveTime == 5 * GameFPS)
	{
		int EnemyCnt = 2;
		D3DXVECTOR3 SpownPoint;

		SpownPoint = D3DXVECTOR3(float(rand() % (int)StageBorder.Right), 0.0f, float(rand() % (int)StageBorder.Top));
			   		
		switch (rand() % 3)
		{
		case 0:
			DecorationManager.decoration.push_back(new Decoration_RedBall(&SpownPoint));
			break;
		case 1:
			DecorationManager.decoration.push_back(new Decoration_BlueBall(&SpownPoint));
			break;
		case 2:
			DecorationManager.decoration.push_back(new Decoration_YellowBall(&SpownPoint));
			break;
		default:
			break;
		}
		

		for (int i = 0; i < EnemyCnt; i++)
		{
			D3DXVECTOR3 Tmp;													//d‚È‚Á‚Ä‚È‚¢‚©‚Ìˆ—‚ð“ü‚ê‚é
			Tmp = D3DXVECTOR3(SpownPoint.x - (rand() % 5 - 15), 0, SpownPoint.z - (rand() % 5 - 15));
			EnemyManager.SetEnemy(D3DXVECTOR3(Tmp));
		}
	}
	
	if (nowWaveTime >= waveLimit)
	{
		return new WavePatternRandom();
	}

	return nullptr;
}
