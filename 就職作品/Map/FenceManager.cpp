#include "FenceManager.h"



FenceManager::FenceManager(int CntX, int CntZ, float OffSetX, float OffSetZ)
{
	fenceData.cntX = CntX;
	fenceData.cntZ = CntZ;
	fenceData.offSetX = OffSetX;
	fenceData.offSetX = OffSetZ;
}

FenceManager::~FenceManager()
{
}

void FenceManager::SetFence()
{
	for (int i = 0; i < fenceData.cntX; i++)	//X
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((i * blockInterval), 0.0f, (fenceData.offSetZ * -1)));
	}

	for (int j = 0; j < fenceData.cntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((fenceData.offSetX * -1), 0.0f, (j * blockInterval)), 90);
	}

	//GameScene::GetStageSize(&StageSizeX, &StageSizeY);
	for (int i = 0; i < fenceData.cntX; i++)	//X
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((i * blockInterval), 0.0f, fenceData.offSetZ + stageSizeZ));		//StageÇÕ2éüå≥ÇæÇ©ÇÁYÇ™Å™
	}

	for (int j = 0; j < fenceData.cntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(fenceData.offSetX + stageSizeX, 0.0f, (j * blockInterval)), 90);
	}
}


void FenceManager::Draw(void)
{
	for (unsigned int i = 0; i < stageFence.size(); i++)
	{
		stageFence[i]->Draw();
	}
}

void FenceManager::SetStageSize(float StageSizeX, float StageSizeZ)
{
	stageSizeX = StageSizeX;
	stageSizeZ = StageSizeZ;
}
