#pragma once
#include<vector>
#include"Enemy.h"
#include"../commonObj/SnowBallManager.h"
#include"../SingletonBase.h"

#define GetEnemyManager EnemyManager::GetInstance()

class EnemyManager : public SingletonBase<EnemyManager>{
	friend class SingletonBase<EnemyManager>;			//SingletonBaseでのインスタンス作成削除は許可
public:
	std::vector<Enemy*> enemy;

	void AllDelete(void);

	//消したいインスタンスの配列番号を渡すとそのインスタンスを削除する
	void DeleteEnemyInstance(unsigned int ite);

	void SetEnemy(D3DXVECTOR3 Pos);
	
	void Draw();
	void Update(SnowBallManager &SnowBallManager, StageBorder &StageBorder);

private:
	~EnemyManager();
};
