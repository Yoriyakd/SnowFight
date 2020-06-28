#pragma once
#include"EnemyStateBase.h"
#include<d3dx9.h>

class ShootSnowBall : public EnemyStateBase{
public:
	ShootSnowBall();
	EnemyStateBase* Action(Enemy &Enemy);

private:
	bool WindUpAnime(Enemy& Enemy);	
	bool ThrowAnime(Enemy& Enemy);
	float windUpAnimeFrame;
	const static float ANIME_SPEED;

	D3DXMATRIX windUpStartMat, windUpEndMat, nowMat;

	float throwAnimeFrame;
	D3DXMATRIX throwStartMat, throwEndMat;
};