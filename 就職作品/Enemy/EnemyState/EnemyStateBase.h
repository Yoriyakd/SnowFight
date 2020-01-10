#pragma once
class Enemy;		//‘O•ûéŒ¾

class EnemyStateBase {
public:
	virtual EnemyStateBase* Action(Enemy& Enemy) = 0;
};