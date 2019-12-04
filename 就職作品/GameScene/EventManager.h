#pragma once
#include"../main.h"
#include"WavePatternBase.h"
#include"WavePattern1.h"
#include"../Item/DecorationBase.h"

//--------------------------------------------
//プレイヤーが直接関係ないイベントを管理するクラス
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	bool Update();

	void AddScore(int Score);
	void DoDecorate(DecorationID ID);			//現状は数だけだが、ノルマに種類などを設ける

	void SetTimeLimit(int TimeLimit_Flame);
	void SetNorm(int Norm);

	int GetRemainingTime_s(void);			//残り時間を秒数で返す
	int GetNowNormCnt(void);
	bool GetNormState(void);
	
private:
	int score;
	int timeLimit_Frame;		//制限時間	0になるとゲーム終了		単位フレーム
	int nowCnt, normCnt;
	bool normState;
	WavePatternBase *wavePattern;
};