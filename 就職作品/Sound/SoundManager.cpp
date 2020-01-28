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
		if (Sound2DMap[_ID][i].IsPlaying() == false)		//�Đ������`�F�b�N
		{
			Sound2DMap[_ID][i].Play();
			return true;	//�Đ�����
		}
	}
	return false;		//���s		//���ׂčĐ���
}

void SoundManager::Initialize()
{
	//�Ƃ肠���������ɒ��ڏ����i�jTEXT���O���t�@�C������ǂݍ���
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
