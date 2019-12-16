#include "MakeSnowBallAnime.h"
const float MakeSnowBallAnime::AnimeSpeed = 0.1f;

MakeSnowBallAnime::MakeSnowBallAnime(D3DXMATRIX * StartMatL, D3DXMATRIX * StartMatR)
{
	flag = true;
	frameCnt = 0;

	startMatL = *StartMatL;
	startMatR = *StartMatR;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotTmpL, EndTransTmpL, EndRotTmpR, EndTransTmpR;

	D3DXMatrixRotationZ(&EndRotTmpL, D3DXToRadian(-130));
	D3DXMatrixRotationZ(&EndRotTmpR, D3DXToRadian(130));
	

	D3DXMatrixTranslation(&EndTransTmpL, -1.5f, -1.5f, 4.0f);		//�J��������̋���
	D3DXMatrixTranslation(&EndTransTmpR, 1.5f, -1.5f, 4.0f);		//�J��������̋���
	

	endMatL = EndRotTmpL * EndTransTmpL;			//�r��˂��o�����ʒu
	endMatR = EndRotTmpR * EndTransTmpR;			//�r��˂��o�����ʒu
	

}

MakeSnowBallAnime::~MakeSnowBallAnime()
{
}

ArmAnimeBase * MakeSnowBallAnime::Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	if (animeFrame <= 1)
	{
		animeFrame += AnimeSpeed;
		
		QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, animeFrame);
		QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);
	}
	else//�r��O�ɏo���A�j���[�V�������I�������ɐ�ʂ���铮��������
	{
		D3DXMATRIX TmpRotMatL, TmpRotMatR;

		frameCnt++;

		D3DXMatrixRotationY(&TmpRotMatL, -(float)D3DXToRadian(sin(frameCnt / 10)));
		D3DXMatrixRotationY(&TmpRotMatR, (float)D3DXToRadian(sin(frameCnt / 10)));
		

		
		*NowMatL = *NowMatL * TmpRotMatL;
		*NowMatR = *NowMatR * TmpRotMatR;
	}
	
	return nullptr;
}
