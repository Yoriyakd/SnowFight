#pragma once
#include"ArmAnimeBase.h"
class ThrowAnime :public ArmAnimeBase {
public:
	ThrowAnime(void);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMat);
private:
	float atOneceRot, endAng, nowAng;		//1�x�ɉ�]����p�x		�I���̊p�x	���݂̊p�x
};
