#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Play(SoundID _ID)
{
	switch (_ID)
	{
	case InGameBGM_ID:
		IngameBGM.Play();
		break;
	default:
		break;
	}
}

void SoundManager::Initialize()
{
	IngameBGM.Initialize();
}

void SoundManager::Update()
{
	IngameBGM.Update();
}
