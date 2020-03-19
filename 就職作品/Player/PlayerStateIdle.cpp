#include"PlayerStateIdle.h"
#include"Player.h"
#include"MakeSnowBallState.h"
#include"../Item/DecorationManager.h"


PlayerStateIdle::PlayerStateIdle(D3DXMATRIX *StartMatL, D3DXMATRIX *StartMatR):animeFrame(0), isMakeKey(false)
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

PlayerStateBase* PlayerStateIdle::Action(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	animeFrame += AnimeSpeed;

	if (animeFrame > 1.0f)
	{
		animeFrame = 1.0f;
	}

	QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, animeFrame);		//�I���̏�ԂɈڍs���L�[�v����
	QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);


	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//�������������ԂȂ�
	{
		if (isShootKey == true)
		{
			if (GetPlayer.IsThrowAnything() == true)
			{
				return new WindUpState(NowMatR);
			}
		}
	}
	else
	{
		isShootKey = true;
	}
	
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if(isMakeKey == true)return nullptr;		//�E�������Ɖ������ςȂ��Ő�ʂ����Ȃ��悤�ɂ��Ă���
		if(GetPlayer.CanMakeSnowBall() == true)
		{
			return new MakeSnowBallState(NowMatL, NowMatR);	
		}
		else
		{
			isMakeKey = true;
			return nullptr;		//�E�����ԂȂ��ʂ����Ȃ�
		}
	}
	else
	{
		isMakeKey = false;
	}
	return nullptr;
}

void PlayerStateIdle::LimitKeepPushShootKey(void)
{
	isShootKey = false;		//1�x�L�[���痣���Ȃ��ƑłĂȂ��悤�ɂ���
}

bool PlayerStateIdle::isShootKey = false;