#pragma once
#include"PlayerStateBase.h"
class PlayerStateIdle :public PlayerStateBase {
public:
	PlayerStateIdle(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~PlayerStateIdle();
	PlayerStateBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);

private:
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;
	bool KeyFlag;
};