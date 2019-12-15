#include "MakeSnowBallAnime.h"
const float MakeSnowBallAnime::AnimeSpeed = 0.1f;

MakeSnowBallAnime::MakeSnowBallAnime(D3DXMATRIX * StartMat)
{
	flag = true;
	frameCnt = 0;

	startMat = *StartMat;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotTmp, EndTransTmp;

	D3DXMatrixRotationZ(&EndRotTmp, D3DXToRadian(130));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 4.0f);		//�J��������̋���

	endMat = EndRotTmp * EndTransTmp;			//�ҋ@�̈ʒu
}

MakeSnowBallAnime::~MakeSnowBallAnime()
{
}

ArmAnimeBase * MakeSnowBallAnime::Anime(D3DXMATRIX * NowMat)
{
	if (animeFrame <= 1)
	{
		animeFrame += AnimeSpeed;
		QuaternionAnime(NowMat, NowMat, &startMat, &endMat, animeFrame);
	}
	else//�r��O�ɏo���A�j���[�V�������I�������ɐ�ʂ���铮��������
	{
		D3DXMATRIX TmpRotMat;

		frameCnt++;

		D3DXMatrixRotationY(&TmpRotMat, D3DXToRadian(sin(frameCnt / 10)));

		*NowMat = *NowMat * TmpRotMat;
	}
	
	return nullptr;
}
