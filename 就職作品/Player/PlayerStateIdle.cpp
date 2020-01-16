#include"PlayerStateIdle.h"
#include"Player.h"


PlayerStateIdle::PlayerStateIdle(D3DXMATRIX * StartMatL, D3DXMATRIX * StartMatR)
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

PlayerStateIdle::~PlayerStateIdle()
{
}

PlayerStateBase* PlayerStateIdle::Anime(D3DXMATRIX * NowMatL, D3DXMATRIX * NowMatR)
{
	animeFrame += AnimeSpeed;

	QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, animeFrame);
	QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);

	if (animeFrame >= 1)
	{
		return new PlayerStateIdle(&endMatL, &endMatR);
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//�������������ԂȂ�
	{
		if (GetPlayer.IsThrowAnything() == true)
		{
			return new WindUpState(NowMatR);
		}
	}
	return nullptr;
}
