#pragma once
#include<vector>
#include"Enemy.h"
class EnemyManager {
private:
	
	
	
public:
	std::vector<Enemy*> enemy;

	EnemyManager();
	~EnemyManager();


	void SetEnemy(D3DXVECTOR3 Pos);
};
