#include "Sound2D.h"

Sound2D::Sound2D()
{
}

Sound2D::~Sound2D()
{
	
}

void Sound2D::Play()
{
	Buffer->Play(0, 0, soundData.LoopFlag);
	IsPlaying();
}

void Sound2D::Stop()
{
	Buffer->Stop();
	Buffer->SetCurrentPosition(0);
}

void Sound2D::Initialize(const SoundInitData &_SoundInitData)
{
	//CSV‚Æ‚©‚©‚ç“Ç‚İ‚Ş
	Buffer = GetResource.GetSound(_SoundInitData.ID);
	soundData = _SoundInitData;
	Buffer->SetVolume(soundData.Volume);
}

bool Sound2D::IsPlaying()
{
	DWORD pdwStatus;
	Buffer->GetStatus(&pdwStatus);
	if ((pdwStatus & DSBSTATUS_PLAYING) == FALSE)
	{
		return false;			//Ä¶’†‚Å‚Í–³‚¢
	}
	return true;
}

int Sound2D::GetMaxPlayCnt(void)
{
	return soundData.MaxPlayCnt;
}
