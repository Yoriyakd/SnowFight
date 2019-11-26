#include "HedgeManager.h"

HedgeManager::HedgeManager(StageBorder * StageBorder)
{
	stageBorder = *StageBorder;

	int FenceCnt = 16;		//16 * 16 = 256 ステージサイズに合わせた数

	for (int i = 0; i < FenceCnt; i++)		//stageTop
	{
		stageHedge.push_back(new StageHedge(&D3DXVECTOR3((16.0f * i) + 8, 4.0f, stageBorder.Top + 2), 90));
	}

	for (int i = 0; i < FenceCnt; i++)		//stageLeft
	{
		stageHedge.push_back(new StageHedge(&D3DXVECTOR3(stageBorder.Left - 2, 4.0f, (16.0f * i) + 8)));
	}

	for (int i = 0; i < FenceCnt; i++)		//stageRight
	{
		stageHedge.push_back(new StageHedge(&D3DXVECTOR3(stageBorder.Right + 2, 4.0f, (16.0f * i) + 8)));
	}
}

HedgeManager::~HedgeManager()
{
}

void HedgeManager::Draw(void)
{
	for (unsigned int i = 0; i < stageHedge.size(); i++)
	{
		stageHedge[i]->Draw();
	}
}

