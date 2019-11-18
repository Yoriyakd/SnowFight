#pragma once
#include"ArmAnimeBase.h"
class ArmRAnimeMid :public ArmAnimeBase {
public:
	ArmRAnimeMid(D3DXMATRIX *StartMat);
	~ArmRAnimeMid();
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);

private:
	const static float AnimeSpeed;
};