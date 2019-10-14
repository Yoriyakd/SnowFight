#include "FenceManager.h"



FenceManager::FenceManager(int CntX, int CntZ, float OffSetX, float OffSetZ)
{
	fenceData.cntX = CntX;
	fenceData.cntZ = CntZ;
	fenceData.offSetX = OffSetX;
	fenceData.offSetZ = OffSetZ;
}

FenceManager::~FenceManager()
{
}

void FenceManager::SetFence()
{
	for (int i = 0; i < fenceData.cntX; i++)	//X
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(0 + (i * blockInterval), 0.0f, (fenceData.offSetZ * -1)));		//配列インデックスをステージの配列の最後から-1して求めている
	}

	for (int j = 0; j < fenceData.cntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((fenceData.offSetX * -1), 0.0f, 0 + (j * blockInterval)), 90);	//配列インデックスをステージの配列の最後から-1して求めている
	}

	for (int i = 0; i < fenceData.cntX; i++)	//X
	{
		stageFence.push_back(new StageFence());				//X = 0からX方向にどんどんのびる									//ここはつまりステージの境界線
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(0 + (i * blockInterval), 0.0f, fenceData.offSetZ + stageSizeZ));		//Stageは2次元だからYが↑	//配列インデックスをステージの配列の最後から-1して求めている
	}

	for (int j = 0; j < fenceData.cntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(fenceData.offSetX + stageSizeX, 0.0f, 0 + (j * blockInterval)), 90);	//配列インデックスをステージの配列の最後から-1して求めている
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
