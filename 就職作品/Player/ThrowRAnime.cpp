#include "ThrowRAnime.h"
#include"ArmRAnimeMid.h"

ThrowRAnime::ThrowRAnime()
{
	atOneceRot = -11;
	nowAng = 0;
	endAng = -150;
}

ArmAnimeBase *ThrowRAnime::Anime(D3DXMATRIX *NowMat)
{
	NowMat->_42 += -0.05;
	NowMat->_43 = 2.5f;
	
	nowAng += atOneceRot;

	D3DXMATRIX RotXTmp;

	D3DXMatrixRotationX(&RotXTmp, D3DXToRadian(atOneceRot));

	*NowMat = RotXTmp * *NowMat;

	if (nowAng <= endAng)
	{
		return new ArmRAnimeMid(NowMat);
	}
	return nullptr;
}
