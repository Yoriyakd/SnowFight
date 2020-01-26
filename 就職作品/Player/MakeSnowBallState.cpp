#include"MakeSnowBallState.h"
#include"PlayerStateIdle.h"
#include"PlayerCamera.h"
#include"Player.h"


MakeSnowBallState::MakeSnowBallState(D3DXMATRIX * StartMatL, D3DXMATRIX * StartMatR)
{
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

MakeSnowBallState::~MakeSnowBallState()
{
}

PlayerStateBase * MakeSnowBallState::Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		GetPlayerCam.SetMakeSnowBallFlag(true);
		if (GetPlayerCam.GetHasPosed() == false)return nullptr;			//ポーズが変更し終わってなかったら抜ける

		GetPlayer.MakeBallStart();		//playerでボールを作り始める

		if (animeFrame <= 1.0f)
		{
			animeFrame += AnimeSpeed;

			QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, animeFrame);
			QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);
			return nullptr;
		}
		
		
		//腕を前に出すアニメーションが終わった後に雪玉を作る動きをする
		{
			D3DXMATRIX TmpRotMatL, TmpRotMatR;

			frameCnt++;			//腕の動きに使う時間経過

			D3DXMatrixRotationY(&TmpRotMatL, -(float)D3DXToRadian(sin(frameCnt / 10)));		//sin関数で揺らす
			D3DXMatrixRotationY(&TmpRotMatR, (float)D3DXToRadian(sin(frameCnt / 10)));

			*NowMatL = *NowMatL * TmpRotMatL;
			*NowMatR = *NowMatR * TmpRotMatR;
		}
	}
	else
	{
		GetPlayerCam.SetMakeSnowBallFlag(false);		//作っている状態を終了する
		GetPlayer.MakeBallEnd();
		return new PlayerStateIdle(NowMatL, NowMatR);
	}
	return nullptr;
}
