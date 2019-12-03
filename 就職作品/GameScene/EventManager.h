#pragma once
#include"../main.h"
#include"WavePatternBase.h"
#include"WavePattern1.h"

//--------------------------------------------
//�v���C���[�����ڊ֌W�Ȃ��C�x���g���Ǘ�����N���X
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	void Update();
	void AddScore(int Score);
	void SetTimeLimit(int TimeLimit_Flame);

	int GetRemainingTime_s(void);			//�c�莞�Ԃ�b���ŕԂ�
	
private:
	int score;
	int timeLimit_Frame;		//��������	0�ɂȂ�ƃQ�[���I��		�P�ʃt���[��
	WavePatternBase *wavePattern;
};