#pragma once
#include"EnemyStateBase.h"
#include<d3dx9.h>

class WindUp_E: public EnemyStateBase {
public:
	WindUp_E();
	EnemyStateBase* Action(Enemy &Enemy);

private:
	float nowRotAng;
	const float ROT_SPEED = 2.0f;
	const float END_ROT = 30.0f;
};
