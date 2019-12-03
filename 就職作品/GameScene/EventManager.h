#pragma once
#include"../main.h"
#include"WavePatternBase.h"
#include"WavePattern1.h"

//--------------------------------------------
//プレイヤーが直接関係ないイベントを管理するクラス
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	void Update();
	void AddScore(int Score);
	void SetTimeLimit(int TimeLimit_Flame);

	int GetRemainingTime_s(void);			//残り時間を秒数で返す
	
private:
	int score;
	int timeLimit_Frame;		//制限時間	0になるとゲーム終了		単位フレーム
	WavePatternBase *wavePattern;
};