#pragma once
#include"../main.h"
class ArmAnimeBase {
public:
	virtual ArmAnimeBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR) = 0;
protected:
};