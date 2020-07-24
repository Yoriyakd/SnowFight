#pragma once
#include"EnemyStateBase.h"
#include<d3dx9.h>

class Throw_E : public EnemyStateBase{
public:
	Throw_E();
	EnemyStateBase* Action(Enemy &Enemy);

private:	
	float nowRotAng;
	const float ROT_SPEED = -8.0f;
	const float END_ROT = -120.0f;
};