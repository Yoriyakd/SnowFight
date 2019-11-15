#pragma once
#include"ArmAnimeBase.h"
class ThrowRAnime :public ArmAnimeBase {
private:
	float atOneceRot, endAng, nowAng;		//1度に回転する角度		終わりの角度	現在の角度
public:
	ThrowRAnime(void);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};
