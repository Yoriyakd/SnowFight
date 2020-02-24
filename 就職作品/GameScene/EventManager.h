#pragma once
#include"../main.h"
#include"../Item/DecorationBase.h"
#include"../Item/DecorationManager.h"
#include"../Enemy/EnemyManager.h"
#include"GameObjectSpawner.h"

//--------------------------------------------
//ノルマを管理するクラス
//--------------------------------------------
class GameNormManager {
public:
	GameNormManager();
	~GameNormManager();
	void Update();		//時間進行

	//void AddScore(int Score);
	void DoDecorate(CarryObjectID ID);			//現状は数だけだが、ノルマに種類などを設ける

	void SetNorm(int Norm);

	int GetNowNormCnt(void);
	bool GetNormState(void);
	
private:
	int score;
	int nowCnt, normCnt;
	bool normState;
};