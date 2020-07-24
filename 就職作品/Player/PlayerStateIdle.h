#pragma once
#include"PlayerStateBase.h"
class PlayerStateIdle  :public PlayerStateBase {
public:
	PlayerStateIdle(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~PlayerStateIdle();
	PlayerStateBase* Action(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
	//1度キーから離さないと打てないようにする
	static void LimitKeepPushShootKey(void);

private:
	const float AnimeSpeed = 0.1f;
	float animeFrame;
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;
	bool isMakeKey;

	static bool isShootKey;		//Playerに変数を持たせるように変更する
};