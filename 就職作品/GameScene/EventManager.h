#pragma once
#include"../main.h"
#include"../Item/DecorationBase.h"
#include"../Item/DecorationManager.h"
#include"../Enemy/EnemyManager.h"
#include"GameObjectSpawner.h"

//--------------------------------------------
//�v���C���[�����ڊ֌W�Ȃ��C�x���g���Ǘ�����N���X
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	bool Update(EnemyManager &EnemyManager, DecorationManager & DecorationManager, StageBorder & StageBorder);

	//void AddScore(int Score);
	void DoDecorate(DecorationID ID);			//����͐����������A�m���}�Ɏ�ނȂǂ�݂���
	void PlayerTakeDamage();

	void SetTimeLimit(int TimeLimit_Flame);
	void SetNorm(int Norm);

	int GetRemainingTime_s(void);			//�c�莞�Ԃ�b���ŕԂ�
	int GetNowNormCnt(void);
	bool GetNormState(void);
	
private:
	int score;
	int timeLimit_Frame;		//��������	0�ɂȂ�ƃQ�[���I��		�P�ʃt���[��
	int nowCnt, normCnt;
	bool normState;
};