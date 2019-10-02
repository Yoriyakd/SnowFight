#include "SetStageData.h"

const float SetStageData::TILE_SIZE = 18.0f;				//宣言時初期化できないのでここで初期化

//===============================================
//private
//===============================================

void SetStageData::SetStageMap(void)
{
	char FileName[16];
	//=================================================================================
	//ファイルオープン
	//=================================================================================

	sprintf_s(FileName, sizeof(FileName), "Map/stage%d.txt", nowStageNo);		//ファイルパス作成

	fopen_s(&fp, FileName, "r");	//fopenのセキュリティ強化版らしい


	//=================================================================================
	//読み取った値をセット
	//=================================================================================
	fscanf_s(fp, "壁:%d\n", &wallNum);
	fscanf_s(fp, "敵:%d\n", &enemyNum);
	fscanf_s(fp, "map\n");					//空読み

	for (int i = 0; i < STAGE_Y; i++)
	{
		for (int j = 0; j < STAGE_X; j++)
		{
			fscanf_s(fp, "%1d ", &StageMap[i][j]);
		}
		fscanf_s(fp, "\n");					//空読み
	}

	fclose(fp);

	wallPos = new D3DXVECTOR3[wallNum];
	enemyPos = new D3DXVECTOR3[enemyNum];			//動的確保する

	int WallIte = 0;
	int EnemyIte = 0;

	//printf_s("%d", &wallNum);

	for (int i = 0; i < STAGE_Y; i++)
	{
		for (int j = 0; j < STAGE_X; j++)
		{
			switch (StageMap[i][j])
			{
			case WALL:
				wallPos[WallIte] = D3DXVECTOR3((float)(j * TILE_SIZE), 0, (float)((STAGE_Y - i) * TILE_SIZE));
				WallIte++;
				break;

			case ENEMY:
				enemyPos[EnemyIte] = D3DXVECTOR3((float)(j * TILE_SIZE), 0, (float)((STAGE_Y - i) * TILE_SIZE));
				EnemyIte++;
				break;

			EMPTY:					//何もしない
				break;
			}
		}
	}

	//int a;
	//fscanf(fp, "壁:%d\n", &a);		//シーク位置は読んだあと移動する
	//fscanf(fp, "%d ", &a);

//	int b[10] = {0,1,2,3,4,5};
//	fwrite(b, sizeof(b), 1, fp);		バイナリ型式でする必要がある
//	fread(b, sizeof(b), 1, fp);			バイナリ型式で


}




//===============================================
//public
//===============================================



SetStageData::SetStageData(int StageNo)
{
	nowStageNo = StageNo;
	SetStageMap();	
}

SetStageData::~SetStageData()
{
	delete wallPos;
	delete enemyPos;
}

int SetStageData::GetWallNum()
{
	return wallNum;
}

int SetStageData::GetEnemyNum()
{
	return enemyNum;
}

D3DXVECTOR3 SetStageData::GetWallData(int WallIte)
{
	return D3DXVECTOR3(wallPos[WallIte]);
}

D3DXVECTOR3 SetStageData::GetEnemyData(int EnemyIte)
{
	return D3DXVECTOR3(enemyPos[EnemyIte]);
}

void SetStageData::GetStageSize(float *StageSizeX, float *StageSizeZ)
{
	*StageSizeX = STAGE_X * TILE_SIZE;
	*StageSizeZ = STAGE_Y * TILE_SIZE;
}
