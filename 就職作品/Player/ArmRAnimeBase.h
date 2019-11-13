#pragma once
#include"../main.h"
class ArmRAnimeBase {
protected:
	D3DXMATRIX endMat, startMat;
	float animeFrame;
public:
	virtual ArmRAnimeBase* Anime(D3DXMATRIX *NowMat) = 0;
};