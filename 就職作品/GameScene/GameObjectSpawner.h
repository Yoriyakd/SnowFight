#pragma once
#include<stdlib.h>
#include"../SingletonBase.h"
#include"../main.h"
struct SpawnerData{
	int SpawnProbability;			//抽選確立(0～100)
	int MaxSpawnAtOnceCnt;			//1度に沸く最大数
	int MinSpawnAtOnceCnt;			//1度に沸く最小数
	int LimitSpawnCnt;				//沸く数の上限
	int LotteryIntervals_f;			//抽選間隔
	int NowFrameCnt;				//現在のフレームカウント
};
class GameObjectSpawner{
public:
	GameObjectSpawner();
	~GameObjectSpawner();
	//抽選確立, 1度に沸く最大数, 1度に沸く最小数, 沸く数の上限, 抽選間隔, 現在のフレームカウント
	void Initialize(SpawnerData &SpawnerData);
	//戻り値で沸く数を返す
	int Updata(void);

private:
	SpawnerData spawnerData; 
};

//listからランダムに沸かせるようにする？
//このクラス内で渡されたクラスのインスタンスを作りたい