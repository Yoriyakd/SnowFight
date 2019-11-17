#pragma once
#include"../main.h"
#include"WavePatternBase.h"
#include"WavePattern1.h"
#include"../Enemy/SetEnemies.h"

//--------------------------------------------
//プレイヤーが直接関係ないイベントを管理するクラス
//--------------------------------------------
class EventManager {
public:
	EventManager();
	~EventManager();
	void Update();
	WavePatternBase *wavePatternBase;
private:
	
};