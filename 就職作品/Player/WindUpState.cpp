#include "WindUpAnime.h"

WindUpAnime::WindUpAnime(D3DXMATRIX *StartMat)
{
	startMatR = *StartMat;
	animeSpeed = 0.2f;		//�Đ����x
	animeFrame = 0.0f;

	D3DXMATRIX EndRotXTmp, EndRotYTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotXTmp, D3DXToRadian(-90));
	D3DXMatrixRotationY(&EndRotYTmp, D3DXToRadian(150));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 0.0f);		//�J��������̋���

	endMatR = EndRotXTmp * EndRotYTmp * EndTransTmp;		//�O�U��̏I�[
}

ArmAnimeBase * WindUpAnime::Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	animeFrame += animeSpeed;

	QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);

	if (animeFrame >= 1)
	{
		animeFrame = 1;
	}
	return nullptr;
}
