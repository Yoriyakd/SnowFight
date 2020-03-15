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
	SoundInitData tmp;

	tmp.ID = TitleBGM_Sound;
	tmp.LoopFlag = true;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "bgm_maoudamashii_xmax02.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = MenuBGM_Sound;
	tmp.LoopFlag = true;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "game_maoudamashii_4_field02.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = InGameBGM_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = -100;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "MusMus-BGM-061.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);
	
	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = Damage_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 5;
	tmp.FileName = "PlayerDamage.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = SnowBallBreak_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 10;
	tmp.FileName = "Snowball_Impact.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
	
	tmp.ID = Throw_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 3;
	tmp.FileName = "Throw.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
	
	tmp.ID = Success_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 4;
	tmp.FileName = "Success.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}
	
	tmp.ID = Clock_Sound;
	tmp.LoopFlag = true;
	tmp.Volume = -10;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "Clock.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = EndWhistle_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "Whistle.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = HeadShoot_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 5;
	tmp.FileName = "EFX SD Cymbal MEINL 10 Splash Dark Crash Unfinished Mallet 01 A.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = XmasTreeHit_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 5;
	tmp.FileName = "XmasTreeHit.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = FinishedMakingSnowBall_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = -100;
	tmp.MaxPlayCnt = 3;
	tmp.FileName = "FinishedMakingSnowBall.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = MakingSnowBall_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "MakingSnowBall.wav";

	Sound2DMap.emplace(tmp.ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	tmp.ID = PickUp_Sound;
	tmp.LoopFlag = false;
	tmp.Volume = 0;
	tmp.MaxPlayCnt = 1;
	tmp.FileName = "PickUp.wav";

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
