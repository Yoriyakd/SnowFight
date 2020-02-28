#pragma once
#include"../main.h"
class PlayerStateBase {
public:
	virtual PlayerStateBase* Action(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR) = 0;
protected:
};