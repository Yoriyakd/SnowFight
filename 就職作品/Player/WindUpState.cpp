#include "WindUpState.h"
#include"ThrowState.h"
#include"Player.h"

WindUpState::WindUpState(D3DXMATRIX *StartMat) : timeCnt_f(0)
{
	startMatR = *StartMat;
	animeSpeed = 0.2f;		//再生速度
	animeFrame = 0.0f;

	D3DXMATRIX EndRotXTmp, EndRotYTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotXTmp, D3DXToRadian(-90));
	D3DXMatrixRotationY(&EndRotYTmp, D3DXToRadian(150));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 0.0f);		//カメラからの距離

	endMatR = EndRotXTmp * EndRotYTmp * EndTransTmp;		//前振りの終端

	GetPlayerCam.SetMoveSpeed(0.3f);		//移動速度を遅くする

}

WindUpState::~WindUpState()
{
	
}

PlayerStateBase * WindUpState::Action(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	animeFrame += animeSpeed;

	QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);

	if (animeFrame >= 1)
	{
		animeFrame = 1;
	}

	timeCnt_f++;
	if (timeCnt_f > MaxPowerTime * GAME_FPS)
	{
		shootPowerPCT = 80;		//最大溜めの速さ
	}
	else
	{
		shootPowerPCT = 30 + 50 * (timeCnt_f / (MaxPowerTime * GAME_FPS));		//30や50は何となくで決めている
	}

	GetPlayer.SetShootPower(shootPowerPCT);

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) == false)
	{
		GetPlayer.SetShootSnowBallFlag(true);
		GetPlayerCam.SetMoveSpeed(0.5f);		//移動速度リセット	//定数化☆
		return new ThrowState();
	}

	//右クリックでキャンセルできるようにする
	//キャンセルメソッドをPlayerに作って呼び出す
	return nullptr;
}
