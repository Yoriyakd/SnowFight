#pragma once
#include<d3dx9.h>
#include"EnemyStateBase.h"
class EngagingMode : public EnemyStateBase{
public:
	EngagingMode();
	EnemyStateBase* Action(Enemy &Enemy);
private:
	int ShootCoolTime;					//��ʔ��˂̃N�[���^�C��
	const float ViewingAngle;
};