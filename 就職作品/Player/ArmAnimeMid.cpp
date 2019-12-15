#include"ArmAnimeMid.h"
const float ArmAnimeMid::AnimeSpeed = 0.1f;

ArmAnimeMid::ArmAnimeMid(D3DXMATRIX *StartMat)
{
	startMat = *StartMat;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotTmp, EndTransTmp;

	D3DXMatrixRotationZ(&EndRotTmp, D3DXToRadian(30));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 3.0f);		//ƒJƒƒ‰‚©‚ç‚Ì‹——£
	
	endMat = EndRotTmp * EndTransTmp;			//‘Ò‹@‚ÌˆÊ’u
}

ArmAnimeMid::~ArmAnimeMid()
{
}

ArmAnimeBase* ArmAnimeMid::Anime(D3DXMATRIX *NowMat)
{
	animeFrame += AnimeSpeed;

	QuaternionAnime(NowMat, NowMat, &startMat, &endMat, animeFrame);

	if (animeFrame >= 1)
	{
		return new ArmAnimeMid(&endMat);
	}
	return nullptr;
}
