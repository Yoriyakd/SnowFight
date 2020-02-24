#pragma once
#include"AddUpdateBase.h"

class TimeUpEffect : public AddUpdateBase {
public:
	GameSceneState AddUpdate();

private:
	int timeUpEffectCnt;
	const int timeUpEffectPlayTime = 90;
};