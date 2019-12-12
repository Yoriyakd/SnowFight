#pragma once
#include"ArmAnimeBase.h"
class ArmAnimeMid :public ArmAnimeBase {
public:
	ArmAnimeMid(D3DXMATRIX *StartMat);
	~ArmAnimeMid();
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);

private:
	const static float AnimeSpeed;
};