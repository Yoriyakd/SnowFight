#pragma once
#include"ArmRAnimeBase.h"
class ArmRAnimeFront :public ArmRAnimeBase {
private:
	const static float AnimeSpeed;
public:
	ArmRAnimeFront(D3DXMATRIX *StartMat);
	~ArmRAnimeFront();
	ArmRAnimeBase* Anime(D3DXMATRIX *NowMat);
};