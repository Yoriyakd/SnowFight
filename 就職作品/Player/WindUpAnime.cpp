#include "WindUpAnime.h"

WindUpAnime::WindUpAnime(D3DXMATRIX *StartMat)
{
	startMatR = *StartMat;
	animeSpeed = 0.2f;		//再生速度
	animeFrame = 0.0f;

	D3DXMATRIX EndRotXTmp, EndRotYTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotXTmp, D3DXToRadian(-90));
	D3DXMatrixRotationY(&EndRotYTmp, D3DXToRadian(150));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 0.0f);		//カメラからの距離

	endMatR = EndRotXTmp * EndRotYTmp * EndTransTmp;		//前振りの終端
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
