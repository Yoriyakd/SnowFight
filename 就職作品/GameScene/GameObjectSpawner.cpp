#include "GameObjectSpawner.h"

GameObjectSpawner::GameObjectSpawner()
{
}

GameObjectSpawner::~GameObjectSpawner()
{
}

void GameObjectSpawner::Initialize(SpawnerData &SpawnerData)
{
	spawnerData = SpawnerData;
}

int GameObjectSpawner::Updata(void)
{
	spawnerData.NowFrameCnt++;

	if (spawnerData.LimitSpawnCnt <= 0)return -1;		//上限の数が0以下になるとこれ以上沸かせない

	if (spawnerData.NowFrameCnt % spawnerData.LotteryIntervals_f == 0)			//抽選間隔毎に実行
	{
		if (IsOverProbabilityValue(spawnerData.SpawnProbability))
		{
			int SpawnCntTmp;

			if (spawnerData.MaxSpawnAtOnceCnt == spawnerData.MinSpawnAtOnceCnt)
			{
				SpawnCntTmp = spawnerData.MaxSpawnAtOnceCnt;
				spawnerData.LimitSpawnCnt -= SpawnCntTmp;
				return spawnerData.MaxSpawnAtOnceCnt;
			}

			SpawnCntTmp = rand() % (spawnerData.MaxSpawnAtOnceCnt - spawnerData.MinSpawnAtOnceCnt) + spawnerData.MinSpawnAtOnceCnt;		//沸く数を上限と下限の間の数で出す

			spawnerData.LimitSpawnCnt -= SpawnCntTmp;

			return SpawnCntTmp;			//出現数を返す
		}
	}

	return -1;
}
