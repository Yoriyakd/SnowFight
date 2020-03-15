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
	Buffer->SetCurrentPosition(0);					//�Đ����擪����(�擪�ȊO����Đ�����ꍇ���\�b�h�ǉ�)
}

void Sound2D::Stop()
{
	Buffer->Stop();
}

void Sound2D::Initialize(const SoundInitData &_SoundInitData)
{
	//CSV�Ƃ�����ǂݍ���
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
		return false;			//�Đ����ł͖���
	}
	return true;
}

int Sound2D::GetMaxPlayCnt(void)
{
	return soundData.MaxPlayCnt;
}
