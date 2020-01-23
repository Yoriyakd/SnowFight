#include "Sound2D.h"

Sound2D::Sound2D()
{
	loopFrag = true;	//��
	volume = 0;
	
}

Sound2D::~Sound2D()
{
	Buffer->Release();
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
	//CSV�Ƃ�����ǂݍ���
	Buffer = GetResource.GetSound(InGameBGM_ID);
}

void Sound2D::Update()
{
	IsPlayeEnd();
}

bool Sound2D::IsPlaying()
{

	return false;
}

void Sound2D::IsPlayeEnd()
{
	
}
