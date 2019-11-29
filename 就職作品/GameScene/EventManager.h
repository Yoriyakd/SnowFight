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
	WavePatternBase *wavePattern;
private:
	int score;
};