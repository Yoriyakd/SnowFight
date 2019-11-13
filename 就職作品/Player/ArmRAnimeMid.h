#pragma once
#include"ArmRAnimeBase.h"
class ArmRAnimeMid :public ArmRAnimeBase {
private:
	const static float AnimeSpeed;
public:
	ArmRAnimeMid(D3DXMATRIX *StartMat);
	~ArmRAnimeMid();
	ArmRAnimeBase* Anime(D3DXMATRIX *NowMat);
};