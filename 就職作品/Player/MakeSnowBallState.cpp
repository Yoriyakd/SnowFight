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
	

	D3DXMatrixTranslation(&EndTransTmpL, -1.5f, -1.5f, 4.0f);		//�J��������̋���
	D3DXMatrixTranslation(&EndTransTmpR, 1.5f, -1.5f, 4.0f);		//�J��������̋���
	

	endMatL = EndRotTmpL * EndTransTmpL;			//�r��˂��o�����ʒu
	endMatR = EndRotTmpR * EndTransTmpR;			//�r��˂��o�����ʒu
}

MakeSnowBallState::~MakeSnowBallState()
{
}

PlayerStateBase * MakeSnowBallState::Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR)
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		GetPlayerCam.SetMakeSnowBallFlag(true);
		if (GetPlayerCam.GetHasPosed() == false)return nullptr;			//�|�[�Y���ύX���I����ĂȂ������甲����

		GetPlayer.MakeBallStart();		//player�Ń{�[�������n�߂�

		if (animeFrame <= 1.0f)
		{
			animeFrame += AnimeSpeed;

			QuaternionAnime(NowMatL, NowMatL, &startMatL, &endMatL, animeFrame);
			QuaternionAnime(NowMatR, NowMatR, &startMatR, &endMatR, animeFrame);
			return nullptr;
		}
		
		
		//�r��O�ɏo���A�j���[�V�������I�������ɐ�ʂ���铮��������
		{
			D3DXMATRIX TmpRotMatL, TmpRotMatR;

			frameCnt++;			//�r�̓����Ɏg�����Ԍo��

			D3DXMatrixRotationY(&TmpRotMatL, -(float)D3DXToRadian(sin(frameCnt / 10)));		//sin�֐��ŗh�炷
			D3DXMatrixRotationY(&TmpRotMatR, (float)D3DXToRadian(sin(frameCnt / 10)));

			*NowMatL = *NowMatL * TmpRotMatL;
			*NowMatR = *NowMatR * TmpRotMatR;
		}
	}
	else
	{
		GetPlayerCam.SetMakeSnowBallFlag(false);		//����Ă����Ԃ��I������
		GetPlayer.MakeBallEnd();
		return new PlayerStateIdle(NowMatL, NowMatR);
	}
	return nullptr;
}
