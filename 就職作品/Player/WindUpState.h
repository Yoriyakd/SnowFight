#pragma once
#include"PlayerStateBase.h"
class WindUpState :public PlayerStateBase {
public:
	WindUpState(D3DXMATRIX *StartMat);
	~WindUpState();
	PlayerStateBase* Action(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	D3DXMATRIX endMatR, startMatR;
	float animeFrame;
	float animeSpeed;

	const float MaxPowerTime = 1.5f;	//ç≈ëÂó≠ÇﬂÇ‹Ç≈Ç…Ç©Ç©ÇÈéûä‘
	float shootPowerPCT;
	int timeCnt_f;
};
