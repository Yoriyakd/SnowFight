#pragma once
#include"EnemyStateBase.h"
class LookForPlayerAnime : public EnemyStateBase {
public:
	LookForPlayerAnime();
	EnemyStateBase* Action(Enemy &Enemy);
private:
	int frameCnt;
};