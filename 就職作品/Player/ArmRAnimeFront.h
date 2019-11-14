#pragma once
#include"ArmAnimeBase.h"
class ArmRAnimeFront :public ArmAnimeBase {
private:
public:
	ArmRAnimeFront(D3DXMATRIX *StartMat);
	~ArmRAnimeFront();
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};