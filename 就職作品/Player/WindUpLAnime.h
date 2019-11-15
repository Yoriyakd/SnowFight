#pragma once
#include"ArmAnimeBase.h"
class WindUpLAnime :public ArmAnimeBase {
public:
	WindUpLAnime(D3DXMATRIX *StartMat);
	ArmAnimeBase *Anime(D3DXMATRIX *NowMat);
};
