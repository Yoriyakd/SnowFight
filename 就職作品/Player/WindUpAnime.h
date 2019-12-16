#pragma once
#include"ArmAnimeBase.h"
class WindUpAnime :public ArmAnimeBase {
public:
	WindUpAnime(D3DXMATRIX *StartMat);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	D3DXMATRIX endMatR, startMatR;
	float animeFrame;
	float animeSpeed;
};
