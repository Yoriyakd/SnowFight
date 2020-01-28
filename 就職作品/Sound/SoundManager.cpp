#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	AllDelete();
}

bool SoundManager::Play(SoundID _ID)
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

void SoundManager::Initialize()
{
	//とりあえずここに直接書く（）TEXT等外部ファイルから読み込む
	SoundInitData tmp{ InGameBGM_ID, false, 0, 1 };

	Sound2DMap.emplace(InGameBGM_ID, new Sound2D[tmp.MaxPlayCnt]);
	
	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}

	/*tmp.ID = Test_ID;
	tmp.LoopFlag = false;
	tmp.Volume = -100;
	tmp.MaxPlayCnt = 3;

	Sound2DMap.emplace(Test_ID, new Sound2D[tmp.MaxPlayCnt]);

	for (auto i = 0; i < tmp.MaxPlayCnt; i++)
	{
		Sound2DMap[tmp.ID][i].Initialize(tmp);
	}*/
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
