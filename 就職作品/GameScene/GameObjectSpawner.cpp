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

	if (spawnerData.LimitSpawnCnt <= 0)return -1;		//����̐���0�ȉ��ɂȂ�Ƃ���ȏ㕦�����Ȃ�

	if (spawnerData.NowFrameCnt % spawnerData.LotteryIntervals_f == 0)			//���I�Ԋu���Ɏ��s
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

			SpawnCntTmp = rand() % (spawnerData.MaxSpawnAtOnceCnt - spawnerData.MinSpawnAtOnceCnt) + spawnerData.MinSpawnAtOnceCnt;		//������������Ɖ����̊Ԃ̐��ŏo��

			spawnerData.LimitSpawnCnt -= SpawnCntTmp;

			return SpawnCntTmp;			//�o������Ԃ�
		}
	}

	return -1;
}
