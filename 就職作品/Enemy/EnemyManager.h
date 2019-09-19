#pragma once
#include<vector>
#include"Enemy.h"
class EnemyManager {
private:
	
	std::vector <SnowBall*> snowBall_E;
	std::vector<Enemy*> enemy;		//�p�u���b�N�ɂ��Ē��ڐG�点��̂͂悭�Ȃ�
public:
	EnemyManager();
	~EnemyManager();

	void SetEnemy(D3DXVECTOR3 Pos);
	void Update();
	void Draw();
};
