#include"ArmRAnimeMid.h"
const float ArmRAnimeMid::AnimeSpeed = 0.05f;

ArmRAnimeMid::ArmRAnimeMid(D3DXMATRIX *StartMat)
{
	startMat = *StartMat;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotTmp, EndTransTmp;

	D3DXMatrixRotationZ(&EndRotTmp, D3DXToRadian(30));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 3.0f);		//カメラからの距離
	
	endMat = EndRotTmp * EndTransTmp;		//歩きモーションの終わり
}

ArmRAnimeMid::~ArmRAnimeMid()
{
}

ArmAnimeBase* ArmRAnimeMid::Anime(D3DXMATRIX *NowMat)
{
	animeFrame += AnimeSpeed;

	QuaternionAnime(NowMat, NowMat, &startMat, &endMat, animeFrame);

	if (animeFrame >= 1)
	{
		return new ArmRAnimeMid(&endMat);
	}
	return nullptr;
}
