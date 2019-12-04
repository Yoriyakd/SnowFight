#pragma once
#include"../main.h"
#include"WavePatternBase.h"
#include"WavePattern1.h"
#include"../Item/DecorationBase.h"

//--------------------------------------------
//�v���C���[�����ڊ֌W�Ȃ��C�x���g���Ǘ�����N���X
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	bool Update();

	void AddScore(int Score);
	void DoDecorate(DecorationID ID);			//����͐����������A�m���}�Ɏ�ނȂǂ�݂���

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
	WavePatternBase *wavePattern;
};