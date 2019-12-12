#pragma once
#include"ArmAnimeBase.h"
class WindUpAnime :public ArmAnimeBase {
public:
	WindUpAnime(D3DXMATRIX *StartMat);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};
