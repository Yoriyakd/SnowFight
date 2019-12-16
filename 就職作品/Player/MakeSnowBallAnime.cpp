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
	

	D3DXMatrixTranslation(&EndTransTmpL, -1.5f, -1.5f, 4.0f);		//カメラからの距離
	D3DXMatrixTranslation(&EndTransTmpR, 1.5f, -1.5f, 4.0f);		//カメラからの距離
	

	endMatL = EndRotTmpL * EndTransTmpL;			//腕を突き出した位置
	endMatR = EndRotTmpR * EndTransTmpR;			//腕を突き出した位置
	

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
	else//腕を前に出すアニメーションが終わった後に雪玉を作る動きをする
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
