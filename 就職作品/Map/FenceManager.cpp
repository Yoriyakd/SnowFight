#include "FenceManager.h"
#include"../GameScene/GameScene.h"


FenceManager::FenceManager()
{
}
FenceManager::FenceManager(int CntX, int CntZ, float OffSetX, float OffSetZ)
{
	for (int i = 0; i < CntX; i++)	//X
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((i * blockSize), 0.0f, OffSetZ));
	}

	for (int j = 0; j < CntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(OffSetX, 0.0f, (j * blockSize)), 90);
	}
	
	GameScene::GetStageSize(&StageSizeX, &StageSizeY);
	for (int i = 0; i < CntX; i++)	//X
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((i * blockSize), 0.0f, (OffSetZ * -1) + StageSizeY));		//Stage‚Í2ŽŸŒ³
	}

	for (int j = 0; j < CntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((OffSetX * -1) + StageSizeX, 0.0f, (j * blockSize)), 90);
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