#pragma once
#include"../main.h"
#include"../Item/DecorationBase.h"
#include"../Item/DecorationManager.h"
#include"../Enemy/EnemyManager.h"
#include"GameObjectSpawner.h"
#include"../SingletonBase.h"

//--------------------------------------------
//ノルマを管理するクラス
//--------------------------------------------

#define GameNorm GameNormManager::GetInstance()

class GameNormManager : public SingletonBase<GameNormManager>{
	friend class SingletonBase<GameNormManager>;
public:
	//void AddScore(int Score);
	//void DoDecorate(CarryObjectID ID);			//現状は数だけだが、ノルマに種類などを設ける
	void DoDecorate(void);			//現状は数だけだが、ノルマに種類などを設ける

	void SetNorm(int Norm);

	int GetNowNormCnt(void);
	bool GetNormState(void);
	
private:
	GameNormManager();
	~GameNormManager();

	int score;
	int nowCnt, normCnt;
	bool normState;
};