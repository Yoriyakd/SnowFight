#pragma once
#include"AddUpdateBase.h"
#include"../main.h"

class GameTime : public AddUpdateBase{
public:
	GameSceneState AddUpdate();
	static void PlayerTakeDamage(int _Penalty);

	static void SetTimeLimit(int TimeLimit_Flame);

	static int GetRemainingTime_s(void);			//�c�莞�Ԃ�b���ŕԂ�
private:
	static int timeLimit_Frame;		//��������	0�ɂȂ�ƃQ�[���I��		�P�ʃt���[��
};