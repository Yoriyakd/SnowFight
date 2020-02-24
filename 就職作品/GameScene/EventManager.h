#pragma once
#include"../main.h"
#include"../Item/DecorationBase.h"
#include"../Item/DecorationManager.h"
#include"../Enemy/EnemyManager.h"
#include"GameObjectSpawner.h"

//--------------------------------------------
//�m���}���Ǘ�����N���X
//--------------------------------------------
class GameNormManager {
public:
	GameNormManager();
	~GameNormManager();
	void Update();		//���Ԑi�s

	//void AddScore(int Score);
	void DoDecorate(CarryObjectID ID);			//����͐����������A�m���}�Ɏ�ނȂǂ�݂���

	void SetNorm(int Norm);

	int GetNowNormCnt(void);
	bool GetNormState(void);
	
private:
	int score;
	int nowCnt, normCnt;
	bool normState;
};