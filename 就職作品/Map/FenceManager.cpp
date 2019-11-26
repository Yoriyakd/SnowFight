#include "FenceManager.h"



FenceManager::FenceManager(StageBorder * StageBorder)
{
	stageBorder = *StageBorder;

	int FenceCnt = 16;		//16 * 16 = 256 �X�e�[�W�T�C�Y�ɍ��킹����

	//for (int i = 0; i < FenceCnt; i++)		//stageTop
	//{
	//	stageFence.push_back(new StageFence(&D3DXVECTOR3((16.0f * i) + 8, 4.0f, stageBorder.Top + 2)));		//�|���̒��S�_�������Ȃ̂ł���ɍ��킹�Ĕz�u
	//}

	//for (int i = 0; i < FenceCnt; i++)		//stageBottom
	//{
	//	stageFence.push_back(new StageFence(&D3DXVECTOR3((16.0f * i) + 8, 4.0f, stageBorder.Bottom - 2)));
	//}

	for (int i = 0; i < FenceCnt; i++)		//stageLeft
	{
		stageFence.push_back(new StageFence(&D3DXVECTOR3(stageBorder.Left - 2, 4.0f, (16.0f * i) + 8), -90));
	}

	for (int i = 0; i < FenceCnt; i++)		//stageRight
	{
		stageFence.push_back(new StageFence(&D3DXVECTOR3(stageBorder.Right + 2, 4.0f, (16.0f * i) + 8), -90));
	}
}

FenceManager::~FenceManager()
{
}

void FenceManager::Draw(void)
{
	for (unsigned int i = 0; i < stageFence.size(); i++)
	{
		stageFence[i]->Draw();
	}
}

