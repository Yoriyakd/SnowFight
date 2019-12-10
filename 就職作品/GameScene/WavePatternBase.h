#pragma once
#include"../Enemy/EnemyManager.h"
class WavePatternBase {
public:
	virtual WavePatternBase* WaveProcessing(EnemyManager &EnemyManager, DecorationManager & DecorationManager, StageBorder & StageBorder) = 0;
protected:
	int waveLimit, nowWaveTime;
private:
};
