#pragma once
#include"EnemyStateBase.h"
#include<d3dx9.h>

class BackOriginalPose : public EnemyStateBase 
{
public:
	BackOriginalPose();
	~BackOriginalPose();

	EnemyStateBase* Action(Enemy &Enemy);
private:
	void MakeInvMat(const D3DXMATRIX &Mat);
	D3DXMATRIX* invRotMat;

	D3DXMATRIX startMat, nowMat, endMat;
	float nowAnimeFrame;
	const float ANIME_SPEED = 0.05f;
};