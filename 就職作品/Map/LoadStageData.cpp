#include "LoadStageData.h"

//===============================================
//public
//===============================================



LoadStageData::LoadStageData(int StageNo)
{
	nowStageNo = StageNo;
}

LoadStageData::~LoadStageData()
{

}


void LoadStageData::SetStageMap(MapObjManager & MapObjManager, EventManager & EventManager, GameObjective & GameObjective, StageBorder & StageBorder)
{
	char FileName[16];
	//=================================================================================
	//ファイルオープン
	//=================================================================================

	sprintf_s(FileName, sizeof(FileName), "data/stage%d.txt", nowStageNo);		//ファイルパス作成

	fopen_s(&fp, FileName, "r");	//fopenのセキュリティ強化版らしい


	//=================================================================================
	//読み取った値をセット
	//=================================================================================
	float StageSizeX, StageSizeZ;

	fscanf_s(fp, "StageSizeX:%f\n", &StageSizeX);
	fscanf_s(fp, "StageSizeY:%f\n", &StageSizeZ);

	StageBorder.Top = StageSizeZ;
	StageBorder.Bottom = 0;
	StageBorder.Left = 0;
	StageBorder.Right = StageSizeX;

	int TimeLimit_frame;		//制限時間
	fscanf_s(fp, "TimeLimit_Frame:%d\n", &TimeLimit_frame);
	EventManager.SetTimeLimit(TimeLimit_frame);

	int NormCnt;
	fscanf_s(fp, "Norm:%d\n", &NormCnt);
	EventManager.SetNorm(NormCnt);
	GameObjective.SetNorm(NormCnt);

	int BenchCnt, TreeCnt, XmasTreeCnt;

	fscanf_s(fp, "Bench:%d\n", &BenchCnt);

	for (int i = 0; i <= BenchCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager.SetBench(TmpPos, TmpAng);
	}

	fscanf_s(fp, "Tree:%d\n", &TreeCnt);

	for (int i = 0; i <= TreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager.SetTree(TmpPos, TmpAng);
	}

	fscanf_s(fp, "Bobbin_Red:%d\n", &TreeCnt);

	for (int i = 0; i <= TreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager.SetBobbin_Red(TmpPos, TmpAng);
	}

	fscanf_s(fp, "XmasTree:%d\n", &XmasTreeCnt);

	for (int i = 0; i <= XmasTreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		fscanf_s(fp, "%f,%f,%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z);
		MapObjManager.SetXmasTree(TmpPos);
	}

	SpawnerData TmpData;

	fscanf_s(fp, "EnemySpawner:\nSpawnProbability:%d\nMaxSpawnAtOnceCnt:%d\nMinSpawnAtOnceCnt:%d\nLimitSpawnCnt:%d\nLotteryIntervals_f:%d\nNowFrameCnt:%d\n", 
				&TmpData.SpawnProbability, &TmpData.MaxSpawnAtOnceCnt, &TmpData.MinSpawnAtOnceCnt, &TmpData.LimitSpawnCnt, &TmpData.LotteryIntervals_f, &TmpData.NowFrameCnt);
	GetSpawnerManager.EnemySpawnerInitialize(TmpData);

	fscanf_s(fp, "DecorationSpawner:\nSpawnProbability:%d\nMaxSpawnAtOnceCnt:%d\nMinSpawnAtOnceCnt:%d\nLimitSpawnCnt:%d\nLotteryIntervals_f:%d\nNowFrameCnt:%d\n",
		&TmpData.SpawnProbability, &TmpData.MaxSpawnAtOnceCnt, &TmpData.MinSpawnAtOnceCnt, &TmpData.LimitSpawnCnt, &TmpData.LotteryIntervals_f, &TmpData.NowFrameCnt);
	GetSpawnerManager.DecorationSpawnerInitialize(TmpData);

	fclose(fp);
}



