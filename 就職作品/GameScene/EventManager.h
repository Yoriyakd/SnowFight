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
	WavePatternBase *wavePattern;
private:
	int score;
};