#pragma once
#include<d3d9.h>
#include<vector>
#include"EnemyDeathAnime.h"
#include"EnemyHatAnime.h"
#include"../commonObj/SnowBall.h"
#include"../Enemy/Enemy.h"

//-----------------------------------------------------------------------------
//�G�����񂾂Ƃ��̃A�j���̃C���X�^�����i�[����N���X
//���V���O���g���N���X
//-----------------------------------------------------------------------------

#define EnemyAnime EnemyAnimeManager::GetInstance()

class EnemyAnimeManager : public SingletonBase <EnemyAnimeManager>{
public:
	friend class SingletonBase<EnemyAnimeManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���

	void NewEnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall);
	void NewEnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot);

	void Draw(void);
	void Updata(void);

private:
	EnemyAnimeManager();
	~EnemyAnimeManager();

	std::vector<EnemyDeathAnime*> enemyDeathAnime;
	std::vector<EnemyHatAnime*> enemyHatAnime;
};

EnemyAnimeManager* SingletonBase<EnemyAnimeManager>::instance = nullptr;