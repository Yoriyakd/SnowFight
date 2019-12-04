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


void LoadStageData::GetStageSize(float *StageSizeX, float *StageSizeZ)
{
	*StageSizeX = stageSizeX;
	*StageSizeZ = stageSizeZ;
}


//===============================================
//private
//===============================================

void LoadStageData::SetStageMap(MapObjManager * MapObjManager, EventManager * EventManager, GameObjective * GameObjective)
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
	fscanf_s(fp, "StageSizeX:%f\n", &stageSizeX);
	fscanf_s(fp, "StageSizeY:%f\n", &stageSizeZ);

	int TimeLimit_frame;		//制限時間
	fscanf_s(fp, "TimeLimit_Frame:%d\n", &TimeLimit_frame);
	EventManager->SetTimeLimit(TimeLimit_frame);

	int NormCnt;
	fscanf_s(fp, "Norm:%d\n", &NormCnt);
	EventManager->SetNorm(NormCnt);
	GameObjective->SetNorm(NormCnt);

	int BenchCnt, TreeCnt, XmasTreeCnt;

	fscanf_s(fp, "Bench:%d\n", &BenchCnt);

	for (int i = 0; i <= BenchCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager->SetBench(TmpPos, TmpAng);
	}

	fscanf_s(fp, "Tree:%d\n", &TreeCnt);

	for (int i = 0; i <= TreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager->SetTree(TmpPos, TmpAng);
	}

	fscanf_s(fp, "Bobbin_Red:%d\n", &TreeCnt);

	for (int i = 0; i <= TreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager->SetBobbin_Red(TmpPos, TmpAng);
	}

	fscanf_s(fp, "XmasTree:%d\n", &XmasTreeCnt);

	for (int i = 0; i <= XmasTreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		fscanf_s(fp, "%f,%f,%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z);
		MapObjManager->SetXmasTree(TmpPos);
	}


	fclose(fp);


	//int a;
	//fscanf(fp, "壁:%d\n", &a);		//シーク位置は読んだあと移動する
	//fscanf(fp, "%d ", &a);

//	int b[10] = {0,1,2,3,4,5};
//	fwrite(b, sizeof(b), 1, fp);		バイナリ型式でする必要がある
//	fread(b, sizeof(b), 1, fp);			バイナリ型式で


}



