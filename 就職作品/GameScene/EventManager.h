#pragma once
#include"../main.h"
#include"WavePatternBase.h"
#include"WavePattern1.h"
#include"../Enemy/SetEnemies.h"

//--------------------------------------------
//�v���C���[�����ڊ֌W�Ȃ��C�x���g���Ǘ�����N���X
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	void Update();
	WavePatternBase *wavePatternBase;
private:
	
};