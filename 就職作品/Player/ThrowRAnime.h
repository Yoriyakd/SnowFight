#pragma once
#include"ArmAnimeBase.h"
class ThrowRAnime :public ArmAnimeBase {
private:
	float atOneceRot, endAng, nowAng;		//1�x�ɉ�]����p�x		�I���̊p�x	���݂̊p�x
public:
	ThrowRAnime(void);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
};
