#pragma once
#include<vector>
#include"Enemy.h"
#include"../commonObj/SnowBallManager.h"
class EnemyManager {
public:
	std::vector<Enemy*> enemy;

	EnemyManager();
	~EnemyManager();

	void AllDelete(void);

	void SetEnemy(D3DXVECTOR3 Pos);
	
	void Draw();
	void Update(SnowBallManager *SnowBallManager);
};
