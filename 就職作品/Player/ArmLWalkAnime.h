#pragma once
#include"ArmAnimeBase.h"
class ArmLWalkAnime :public ArmAnimeBase {
public :
	ArmLWalkAnime(D3DXMATRIX *StartMat);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};
