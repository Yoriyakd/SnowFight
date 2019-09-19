#pragma once
#include<vector>
#include"Enemy.h"
class EnemyManager {
private:
	
	std::vector <SnowBall*> snowBall_E;
	std::vector<Enemy*> enemy;		//パブリックにして直接触らせるのはよくない
public:
	EnemyManager();
	~EnemyManager();

	void SetEnemy(D3DXVECTOR3 Pos);
	void Update();
	void Draw();
};
