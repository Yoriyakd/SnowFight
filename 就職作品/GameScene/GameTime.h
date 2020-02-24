#pragma once
#include"AddUpdateBase.h"
#include"../main.h"

class GameTime : public AddUpdateBase{
public:
	GameSceneState AddUpdate();
	static void PlayerTakeDamage(int _Penalty);

	static void SetTimeLimit(int TimeLimit_Flame);

	static int GetRemainingTime_s(void);			//残り時間を秒数で返す
private:
	static int timeLimit_Frame;		//制限時間	0になるとゲーム終了		単位フレーム
};