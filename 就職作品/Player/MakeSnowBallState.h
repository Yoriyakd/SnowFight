#pragma once
#include"PlayerStateBase.h"
class MakeSnowBallState : public PlayerStateBase{
public:
	MakeSnowBallState(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~MakeSnowBallState();
	PlayerStateBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	const float AnimeSpeed = 0.1f;
	float animeFrame;
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;

	int frameCnt;
	D3DXMATRIX TmpRotZ;
};