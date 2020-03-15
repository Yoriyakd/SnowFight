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
	Buffer->SetCurrentPosition(0);					//再生時先頭から(先頭以外から再生する場合メソッド追加)
}

void Sound2D::Stop()
{
	Buffer->Stop();
}

void Sound2D::Initialize(const SoundInitData &_SoundInitData)
{
	//CSVとかから読み込む
	Buffer = GetResource.GetSound(_SoundInitData.FileName);
	soundData = _SoundInitData;
	Buffer->SetVolume(soundData.Volume);
}

bool Sound2D::IsPlaying()
{
	DWORD pdwStatus;
	Buffer->GetStatus(&pdwStatus);
	if ((pdwStatus & DSBSTATUS_PLAYING) == FALSE)
	{
		return false;			//再生中では無い
	}
	return true;
}

int Sound2D::GetMaxPlayCnt(void)
{
	return soundData.MaxPlayCnt;
}
