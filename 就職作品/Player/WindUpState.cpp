#include "WindUpState.h"
#include"ThrowState.h"
#include"Player.h"

WindUpState::WindUpState(D3DXMATRIX *StartMat) : timeCnt_f(0)
{
	startMatR = *StartMat;
	animeSpeed = 0.2f;		//�Đ����x
	animeFrame = 0.0f;

	D3DXMATRIX EndRotXTmp, EndRotYTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotXTmp, D3DXToRadian(-90));
	D3DXMatrixRotationY(&EndRotYTmp, D3DXToRadian(150));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -1.5f, 0.0f);		//�J��������̋���

	endMatR = EndRotXTmp * EndRotYTmp * EndTransTmp;		//�O�U��̏I�[

	GetPlayerCam.SetMoveSpeed(0.3f);		//�ړ����x��x������

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
		shootPowerPCT = 80;		//�ő嗭�߂̑���
	}
	else
	{
		shootPowerPCT = 30 + 50 * (timeCnt_f / (MaxPowerTime * GAME_FPS));		//30��50�͉��ƂȂ��Ō��߂Ă���
	}

	GetPlayer.SetShootPower(shootPowerPCT);

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) == false)
	{
		GetPlayer.SetShootSnowBallFlag(true);
		GetPlayerCam.SetMoveSpeed(0.5f);		//�ړ����x���Z�b�g	//�萔����
		return new ThrowState();
	}

	//�E�N���b�N�ŃL�����Z���ł���悤�ɂ���
	//�L�����Z�����\�b�h��Player�ɍ���ČĂяo��
	return nullptr;
}
