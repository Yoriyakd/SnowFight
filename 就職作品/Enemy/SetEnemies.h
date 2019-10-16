#pragma once
#include"../main.h"
#include"../Enemy/EnemyManager.h"
class SetEnemies {
private:
	float stageSizeX, stageSizeZ;

public:
	SetEnemies();
	~SetEnemies();
	void SetStageSize(float, float);

	 void SetEnemy();
};