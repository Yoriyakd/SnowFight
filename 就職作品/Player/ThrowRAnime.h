#pragma once
#include"ArmAnimeBase.h"
class ThrowRAnime :public ArmAnimeBase {
public:
	ThrowRAnime(void);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
private:
	float atOneceRot, endAng, nowAng;		//1�x�ɉ�]����p�x		�I���̊p�x	���݂̊p�x
};
