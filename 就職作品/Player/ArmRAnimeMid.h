#pragma once
#include"ArmAnimeBase.h"
class ArmRAnimeMid :public ArmAnimeBase {
private:
	const static float AnimeSpeed;
public:
	ArmRAnimeMid(D3DXMATRIX *StartMat);
	~ArmRAnimeMid();
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};