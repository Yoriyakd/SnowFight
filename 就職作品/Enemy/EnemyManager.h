#pragma once
#include<vector>
#include"Enemy.h"
#include"../commonObj/SnowBallManager.h"
#include"../SingletonBase.h"

#define GetEnemyManager EnemyManager::GetInstance()

class EnemyManager : public SingletonBase<EnemyManager>{
	friend class SingletonBase<EnemyManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	std::vector<Enemy*> enemy;

	void AllDelete(void);

	//���������C���X�^���X�̔z��ԍ���n���Ƃ��̃C���X�^���X���폜����
	void DeleteEnemyInstance(unsigned int ite);

	void SetEnemy(D3DXVECTOR3 Pos);
	
	void Draw();
	void Update(SnowBallManager &SnowBallManager, StageBorder &StageBorder);

private:
	~EnemyManager();
};
