#include "FenceManager.h"



FenceManager::FenceManager(StageBorder * StageBorder)
{
	stageBorder = *StageBorder;

	int FenceCnt = 16;		//16 * 16 = 256 ステージサイズに合わせた数

	//for (int i = 0; i < FenceCnt; i++)		//stageTop
	//{
	//	stageFence.push_back(new StageFence(&D3DXVECTOR3((16.0f * i) + 8, 4.0f, stageBorder.Top + 2)));		//板ポリの中心点が中央なのでそれに合わせて配置
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

