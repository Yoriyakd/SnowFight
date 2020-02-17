#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	AllDelete();
}

bool SoundManager::Play2D(SoundID _ID)
{
	const int CNT = Sound2DMap[_ID][0].GetMaxPlayCnt();

	for (auto i = 0; i < CNT; i++)
	{
		if (Sound2DMap[_ID][i].IsPlaying() == false)		//再生中かチェック
		{
			Sound2DMap[_ID][i].Play();
			return true;	//再生成功
		}
	}
	return false;		//失敗		//すべて再生中
}

void SoundManager::Stop(SoundID _ID)
{
	const int CNT = Sound2DMap[_ID][0].GetMaxPlayCnt();

	for (auto i = 0; i < CNT; i++)
	{
		Sound2DMap[_ID][i].Stop();
	}
}

void SoundManager::AllStop()
{
	for (auto ite = begin(Sound2DMap); ite != end(Sound2DMap); ite++)
	{
		const int CNT = ite->second[0].GetMaxPlayCnt();

		for (auto i = 0; i < CNT; i++)
		{
			ite->second[i].Stop();
		}
	}
}

void SoundManager::Initialize()
{
	//とりあえずここに直接書く(TEXT等外部ファイルから読み込む)
	SoundInitData tmp{ InGameBGM_SOUND, false, -100, 1 };

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);
	
	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = SnowBallHit_SOUND;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 10;

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
	
	tmp.ID = Throw_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 3;

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
	
	tmp.ID = Success_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 2;

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
	
	tmp.ID = Clock_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = EndWhistle_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
}

void SoundManager::Update()
{
}

void SoundManager::AllDelete()
{
	for (auto ite = begin(Sound2DMap); ite != end(Sound2DMap); ite++)
	{
		delete[] ite->second;
	}
}
