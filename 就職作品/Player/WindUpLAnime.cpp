#include "WindUpLAnime.h"

WindUpLAnime::WindUpLAnime(D3DXMATRIX *StartMat)
{
	startMat = *StartMat;
	animeSpeed = 0.01f;		//再生速度
	animeFrame = 0.0f;

	D3DXMATRIX EndRotXTmp, EndRotYTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotXTmp, D3DXToRadian(-90));
	D3DXMatrixRotationY(&EndRotYTmp, D3DXToRadian(120));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 2.0f);		//カメラからの距離

	endMat = EndRotXTmp * EndRotYTmp * EndTransTmp;				//アニメの終わりの位置の行列
}

ArmAnimeBase * WindUpLAnime::Anime(D3DXMATRIX *NowMat)
{
	animeFrame += animeSpeed;

	QuaternionAnime(NowMat, NowMat, &startMat, &endMat, animeFrame);

	if (animeFrame <= 1)
	{
		animeFrame = 1;
	}
	return nullptr;
}
