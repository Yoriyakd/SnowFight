#pragma once
#include"ArmAnimeBase.h"
class ThrowAnime :public ArmAnimeBase {
public:
	ThrowAnime(void);
	ArmAnimeBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	float atOneceRot, endAng, nowAng;		//1度に回転する角度		終わりの角度	現在の角度
	const float shootAng;							//手から射出する角度(雪玉を消すタイミングの角度)
};
