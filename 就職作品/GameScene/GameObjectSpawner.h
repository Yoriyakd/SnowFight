#pragma once
#include<stdlib.h>
#include"../SingletonBase.h"
#include"../main.h"
struct SpawnerData{
	int SpawnProbability;			//���I�m��(0�`100)
	int MaxSpawnAtOnceCnt;			//1�x�ɕ����ő吔
	int MinSpawnAtOnceCnt;			//1�x�ɕ����ŏ���
	int LimitSpawnCnt;				//�������̏��
	int LotteryIntervals_f;			//���I�Ԋu
	int NowFrameCnt;				//���݂̃t���[���J�E���g
};
class GameObjectSpawner{
public:
	GameObjectSpawner();
	~GameObjectSpawner();
	//���I�m��, 1�x�ɕ����ő吔, 1�x�ɕ����ŏ���, �������̏��, ���I�Ԋu, ���݂̃t���[���J�E���g
	void Initialize(SpawnerData &SpawnerData);
	//�߂�l�ŕ�������Ԃ�
	int Updata(void);

private:
	SpawnerData spawnerData; 
};

//list���烉���_���ɕ�������悤�ɂ���H
//���̃N���X���œn���ꂽ�N���X�̃C���X�^���X����肽��