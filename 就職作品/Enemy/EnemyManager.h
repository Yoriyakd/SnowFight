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

	//���������C���X�^���X�̔z��ԍ���n���Ƃ��̃C���X�^���X���폜����
	void DeleteInstance(unsigned int ite);

	void SetEnemy(D3DXVECTOR3 Pos);
	
	void Draw();
	void Update(Player &Player, SnowBallManager &SnowBallManager, StageBorder &StageBorder);
};
