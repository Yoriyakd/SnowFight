#pragma once
#include"PlayerStateBase.h"
class ThrowState :public PlayerStateBase {
public:
	ThrowState(void);
	PlayerStateBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	float atOneceRot, endAng, nowAng;		//1度に回転する角度		終わりの角度	現在の角度
	const float shootAng;							//手から射出する角度(雪玉を消すタイミングの角度)
};
