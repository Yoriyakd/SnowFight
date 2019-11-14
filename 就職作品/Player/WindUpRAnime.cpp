#include "WindUpRAnime.h"

WindUpRAnime::WindUpRAnime(D3DXMATRIX *StartMat)
{
	startMat = *StartMat;
	animeSpeed = 0.01;		//�Đ����x
	animeFrame = 0.0f;

	D3DXMATRIX EndRotXTmp, EndRotYTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotXTmp, D3DXToRadian(-90));
	D3DXMatrixRotationY(&EndRotYTmp, D3DXToRadian(120));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 2.0f);		//�J��������̋���

	endMat = EndRotXTmp * EndRotYTmp * EndTransTmp;		//�O�U��̏I�[
}

ArmAnimeBase * WindUpRAnime::Anime(D3DXMATRIX *NowMat)
{
	animeFrame += animeSpeed;

	QuaternionAnime(NowMat, NowMat, &startMat, &endMat, animeFrame);

	if (animeFrame >= 1)
	{
		animeFrame = 1;
	}
	return nullptr;
}
