#include "Sound2D.h"

Sound2D::Sound2D()
{
	loopFrag = false;	//‰¼
	volume = 0;
	
}

Sound2D::~Sound2D()
{
	
}

void Sound2D::Play()
{
	Buffer->Play(0, 0, loopFrag);
}

void Sound2D::Stop()
{
	Buffer->Stop();
}

void Sound2D::Initialize()
{
	//CSV‚Æ‚©‚©‚ç“Ç‚Ýž‚Þ
	Buffer = GetResource.GetSound(InGameBGM_ID);
}

void Sound2D::Update()
{
	IsPlaying();
}

bool Sound2D::IsPlaying()
{
	DWORD pdwStatus;
	Buffer->GetStatus(&pdwStatus);
	if ((pdwStatus & DSBSTATUS_PLAYING) == FALSE)
	{
		return false;
	}
	return true;
}