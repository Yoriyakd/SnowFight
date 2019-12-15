#pragma once
#include"ArmAnimeBase.h"
class MakeSnowBallAnime : public ArmAnimeBase{
public:
	MakeSnowBallAnime(D3DXMATRIX *StartMat);
	~MakeSnowBallAnime();
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
private:
	const static float AnimeSpeed;
	D3DXMATRIX endMat, startMat;
	float animeFrame;
	bool flag;
	int frameCnt;
	D3DXMATRIX TmpRotZ;
};