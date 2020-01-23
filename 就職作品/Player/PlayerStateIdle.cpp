#include"PlayerStateIdle.h"
#include"Player.h"
#include"MakeSnowBallState.h"
#include"../Item/DecorationManager.h"


PlayerStateIdle::PlayerStateIdle(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR):KeyFlag(false)
{
	startMatL = *StartMatL;
	startMatR = *StartMatR;

	D3DXMATRIX EndRotRTmp, EndTransRTmp, EndRotZLTmp, EndRotXLTmp, EndTransLTmp;

	D3DXMatrixRotationZ(&EndRotZLTmp, D3DXToRadian(-90));
	D3DXMatrixRotationX(&EndRotXLTmp, D3DXToRadian(90));
	D3DXMatrixTranslation(&EndTransLTmp, -1.8f, -1.5f, -2.0f);		//�J��������̋���

	endMatL = EndRotZLTmp * EndRotXLTmp * EndTransLTmp;			//�ҋ@�̈ʒu

	D3DXMatrixRotationZ(&EndRotRTmp, D3DXToRadian(30));
	D3DXMatrixTranslation(&EndTransRTmp, 1.8f, -1.5f, 3.0f);		//�J��������̋���

	endMatR = EndRotRTmp * EndTransRTmp;			//�ҋ@�̈ʒu
}

PlayerStateIdle::~PlayerStateIdle()
{
}

PlayerStateBase* PlayerStateIdle::Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{

	QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, 1.0f);		//��ɏI���̏�Ԃ��L�[�v����
	QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, 1.0f);


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//�������������ԂȂ�
	{
		if (GetPlayer.IsThrowAnything() == true)
		{
			return new WindUpState(NowMatR);
		}
	}
	
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if(KeyFlag == true)return nullptr;		//�E�������Ɖ������ςȂ��Ő�ʂ����Ȃ��悤�ɂ��Ă���
		if(GetPlayer.CanMakeSnowBall() == true)
		{
			return new MakeSnowBallState(NowMatL, NowMatR);	
		}
		else
		{
			KeyFlag = true;
			return nullptr;		//�E�����ԂȂ��ʂ����Ȃ�(�V�����E���Ȃ����߂��Ƀf�R���[�V�����������č��Ȃ��Ƃ����󋵂��������遙)
		}
	}
	else
	{
		KeyFlag = false;
	}
	return nullptr;
}
