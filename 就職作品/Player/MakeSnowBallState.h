#pragma once
#include"PlayerStateBase.h"
class MakeSnowBallState : public PlayerStateBase{
public:
	MakeSnowBallState(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~MakeSnowBallState();
	PlayerStateBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	const float AnimeSpeed = 0.3f;
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;
	float animeFrame;

	int frameCnt;
	D3DXMATRIX TmpRotZ;
};