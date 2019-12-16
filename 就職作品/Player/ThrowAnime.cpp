#include "ThrowAnime.h"
#include"ArmAnimeMid.h"

ThrowAnime::ThrowAnime()
{
	atOneceRot = -11;
	nowAng = 0;
	endAng = -150;
}

ArmAnimeBase *ThrowAnime::Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	NowMatR->_42 += -0.1f;
	NowMatR->_43 = 2.5f;
	
	nowAng += atOneceRot;

	D3DXMATRIX RotXTmp;

	D3DXMatrixRotationX(&RotXTmp, D3DXToRadian(atOneceRot));

	*NowMatR = RotXTmp * *NowMatR;

	if (nowAng <= endAng)
	{
		return new ArmAnimeIdle(NowMatL, NowMatR);
	}
	return nullptr;
}
