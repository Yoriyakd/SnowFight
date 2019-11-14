#pragma once
#include"../main.h"
class ArmAnimeBase {
protected:
	D3DXMATRIX endMat, startMat;
	float animeFrame;
	float animeSpeed;
public:
	virtual ArmAnimeBase* Anime(D3DXMATRIX *NowMat) = 0;
};