#include"ArmRAnimeFront.h"
#include"ArmRAnimeMid.h"

ArmRAnimeFront::ArmRAnimeFront(D3DXMATRIX *StartMat)
{
	startMat = *StartMat;
	animeSpeed = 0.05;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotTmp, D3DXToRadian(-30));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -2.5f, 5.5f);		//カメラからの距離

	endMat = EndRotTmp * EndTransTmp;		//前振りの終端
}

ArmRAnimeFront::~ArmRAnimeFront()
{
}

ArmAnimeBase* ArmRAnimeFront::Anime(D3DXMATRIX *NowMat)
{
	animeFrame += animeSpeed;

	QuaternionAnime(NowMat, NowMat, &startMat, &endMat, animeFrame);

	if (animeFrame >= 1)
	{
		return new ArmRAnimeMid(NowMat);
	}
	return nullptr;
}
