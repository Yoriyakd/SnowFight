#include "ThrowAnime.h"
#include"ArmAnimeMid.h"

ThrowAnime::ThrowAnime()
{
	atOneceRot = -11;
	nowAng = 0;
	endAng = -150;
}

ArmAnimeBase *ThrowAnime::Anime(D3DXMATRIX *NowMat)
{
	NowMat->_42 += -0.05f;
	NowMat->_43 = 2.5f;
	
	nowAng += atOneceRot;

	D3DXMATRIX RotXTmp;

	D3DXMatrixRotationX(&RotXTmp, D3DXToRadian(atOneceRot));

	*NowMat = RotXTmp * *NowMat;

	if (nowAng <= endAng)
	{
		return new ArmAnimeMid(NowMat);
	}
	return nullptr;
}
