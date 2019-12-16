#include"ArmAnimeMid.h"
const float ArmAnimeIdle::AnimeSpeed = 0.1f;

ArmAnimeIdle::ArmAnimeIdle(D3DXMATRIX * StartMatL, D3DXMATRIX * StartMatR)
{
	startMatL = *StartMatL;
	startMatR = *StartMatR;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotRTmp, EndTransRTmp, EndRotZLTmp, EndRotXLTmp, EndTransLTmp;

	D3DXMatrixRotationZ(&EndRotZLTmp, D3DXToRadian(-90));
	D3DXMatrixRotationX(&EndRotXLTmp, D3DXToRadian(90));
	D3DXMatrixTranslation(&EndTransLTmp, -1.8f, -1.5f, -2.0f);		//�J��������̋���

	endMatL = EndRotZLTmp * EndRotXLTmp * EndTransLTmp;			//�ҋ@�̈ʒu

	D3DXMatrixRotationZ(&EndRotRTmp, D3DXToRadian(30));
	D3DXMatrixTranslation(&EndTransRTmp, 1.8f, -1.5f, 3.0f);		//�J��������̋���

	endMatR = EndRotRTmp * EndTransRTmp;			//�ҋ@�̈ʒu
}

ArmAnimeIdle::~ArmAnimeIdle()
{
}

ArmAnimeBase* ArmAnimeIdle::Anime(D3DXMATRIX * NowMatL, D3DXMATRIX * NowMatR)
{
	animeFrame += AnimeSpeed;

	QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, animeFrame);
	QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);

	if (animeFrame >= 1)
	{
		return new ArmAnimeIdle(&endMatL, &endMatR);
	}
	return nullptr;
}
