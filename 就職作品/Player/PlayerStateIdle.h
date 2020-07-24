#pragma once
#include"PlayerStateBase.h"
class PlayerStateIdle  :public PlayerStateBase {
public:
	PlayerStateIdle(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR);
	~PlayerStateIdle();
	PlayerStateBase* Action(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
	//1�x�L�[���痣���Ȃ��ƑłĂȂ��悤�ɂ���
	static void LimitKeepPushShootKey(void);

private:
	const float AnimeSpeed = 0.1f;
	float animeFrame;
	D3DXMATRIX endMatL, startMatL, endMatR, startMatR;
	bool isMakeKey;

	static bool isShootKey;		//Player�ɕϐ�����������悤�ɕύX����
};