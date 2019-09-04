#include "Stage.h"

Ground* ground;

const float Stage:: TILE_SIZE = 6.0f;				//宣言時初期化できないのでここで初期化

//===============================================
//private
//===============================================

void Stage::SetStageMap(void)
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

	int enemyIte = 0;

	//printf_s("%d", &wallNum);

	for (int i = 0; i < STAGE_Y; i++)
	{
		for (int j = 0; j < STAGE_X; j++)
		{
			switch (StageMap[i][j])
			{
			case WALL:				//壁は後回し
				break;

			case ENEMY:
				enemyPos[enemyIte] = D3DXVECTOR3((float)((STAGE_X - j) * TILE_SIZE), 0, (float)((STAGE_Y - i) * TILE_SIZE));
				enemyIte++;
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



Stage::Stage(int stageNo)
{
	nowStageNo = stageNo;
	SetStageMap();
	ground = new Ground;
	for (int i = 0; i < enemyNum; i++)
	{
		enemy.push_back(new Enemy(enemyPos[i]));
	}
}

Stage::~Stage()
{
	delete wallPos;
	delete enemyPos;
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		delete enemy[i];

	}
		enemy.clear();
}

void Stage::Draw()
{
	ground->Draw();
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw();
	}
}
