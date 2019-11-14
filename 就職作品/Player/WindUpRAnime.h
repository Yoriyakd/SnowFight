#pragma once
#include"ArmAnimeBase.h"
class WindUpRAnime :public ArmAnimeBase {
public:
	WindUpRAnime(D3DXMATRIX *StartMat);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};
