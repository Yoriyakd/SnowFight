#pragma once
#include"WavePatternBase.h"
class WavePatternRandom :public WavePatternBase {
public:
	WavePatternRandom();
	WavePatternBase* WaveProcessing(EnemyManager &EnemyManagers, DecorationManager & DecorationManager, StageBorder & StageBorder);
private:
};
