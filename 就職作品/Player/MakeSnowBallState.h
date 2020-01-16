#pragma once
#include"PlayerStateBase.h"
class MakeSnowBallAnime : public PlayerStateBase{
public:
	MakeSnowBallAnime(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~MakeSnowBallAnime();
	PlayerStateBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	const static float AnimeSpeed;
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;
	float animeFrame;
	bool flag;
	int frameCnt;
	D3DXMATRIX TmpRotZ;
};