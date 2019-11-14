#pragma once
#include"ArmAnimeBase.h"
class ThrowRAnime :public ArmAnimeBase {
public:
	ThrowRAnime(D3DXMATRIX *StartMat);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};
