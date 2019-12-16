#pragma once
#include"ArmAnimeBase.h"
class ArmAnimeIdle :public ArmAnimeBase {
public:
	ArmAnimeIdle(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~ArmAnimeIdle();
	ArmAnimeBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);

private:
	const float AnimeSpeed = 0.1f;
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;
	float animeFrame;
};