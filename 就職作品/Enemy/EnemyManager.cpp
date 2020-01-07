#include "EnemyManager.h"

EnemyManager::~EnemyManager()
{
	AllDelete();
}

void EnemyManager::AllDelete(void)
{
	for (auto *Enemy : enemy)
	{
		delete Enemy;
	}
	enemy.clear();
}

void EnemyManager::DeleteEnemyInstance(unsigned int ite)
{
	delete enemy[ite];
	enemy.erase(enemy.begin() + ite);
}

void EnemyManager::SetEnemy(D3DXVECTOR3 Pos)
{
	enemy.push_back(new Enemy(Pos));
}

void EnemyManager::Draw()
{
	for (auto *Enemy : enemy)
	{
		Enemy->Draw();
	}
}

void EnemyManager::Update(Player & Player, SnowBallManager & SnowBallManager, StageBorder & StageBorder)
{
	for (unsigned int i = 0; i < enemy.size(); i++)		//�^���_����signed�ɂȂ邽�߃_���݂���
	{
		enemy[i]->Update(Player, SnowBallManager, StageBorder);
		//D3DXVECTOR3 PushOutVec;		//�����ꂽ�Ƃ��Ɉړ�����x�N�g�� ��
		for (unsigned int j = 0; j < enemy.size(); j++)
		{
			if (j == i)continue;		//�����G�Ȃ�X�L�b�v
			//PushOutVec = enemy[i]->CheckOverlapEnemies(&enemy[j]->GetPos());				//�G���m���d�Ȃ�Ȃ��悤�ɂ��鏈���@�������������悤�ɂ���Ƃ�����
			enemy[i]->CheckOverlapEnemies(&enemy[j]->GetPos());				//�G���m���d�Ȃ�Ȃ��悤�ɂ��鏈��
		}
	}
}
