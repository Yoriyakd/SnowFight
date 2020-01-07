#pragma once
#include"../SingletonBase.h"
#include"GameObjectSpawner.h"
#include"../Item/DecorationManager.h"
#include"../Enemy/EnemyManager.h"
#include"../main.h"

#define GetSpawnerManager SpawnerManager::GetInstance()

class SpawnerManager : public SingletonBase<SpawnerManager>{
	friend class SingletonBase<SpawnerManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	void EnemySpawnerInitialize(SpawnerData &SpawnerData);
	void DecorationSpawnerInitialize(SpawnerData &SpawnerData);

	void Update(StageBorder& StageBorder);
private:
	~SpawnerManager();

	GameObjectSpawner *enemySpawner;

	GameObjectSpawner *decorationSpawner;
};

SpawnerManager* SingletonBase<SpawnerManager>::instance = nullptr;
