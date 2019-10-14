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
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(0 + (i * blockInterval), 0.0f, (fenceData.offSetZ * -1)));		//�z��C���f�b�N�X���X�e�[�W�̔z��̍Ōォ��-1���ċ��߂Ă���
	}

	for (int j = 0; j < fenceData.cntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3((fenceData.offSetX * -1), 0.0f, 0 + (j * blockInterval)), 90);	//�z��C���f�b�N�X���X�e�[�W�̔z��̍Ōォ��-1���ċ��߂Ă���
	}

	for (int i = 0; i < fenceData.cntX; i++)	//X
	{
		stageFence.push_back(new StageFence());				//X = 0����X�����ɂǂ�ǂ�̂т�									//�����͂܂�X�e�[�W�̋��E��
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(0 + (i * blockInterval), 0.0f, fenceData.offSetZ + stageSizeZ));		//Stage��2����������Y����	//�z��C���f�b�N�X���X�e�[�W�̔z��̍Ōォ��-1���ċ��߂Ă���
	}

	for (int j = 0; j < fenceData.cntZ; j++)	//Z
	{
		stageFence.push_back(new StageFence());
		stageFence[stageFence.size() - 1]->SetMat(D3DXVECTOR3(fenceData.offSetX + stageSizeX, 0.0f, 0 + (j * blockInterval)), 90);	//�z��C���f�b�N�X���X�e�[�W�̔z��̍Ōォ��-1���ċ��߂Ă���
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
