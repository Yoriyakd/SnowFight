#pragma once
class Enemy;		//�O���錾

class EnemyStateBase {
public:
	virtual EnemyStateBase* Action(Enemy& Enemy) = 0;
};