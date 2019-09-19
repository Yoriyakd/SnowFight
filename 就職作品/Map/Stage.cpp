#include "Stage.h"


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



Stage::Stage(int StageNo)
{
	nowStageNo = StageNo;
	SetStageMap();
	ground = new Ground;
	enemyManager = new EnemyManager;

	for (int i = 0; i < wallNum; i++)
	{
		wall.push_back(new Wall(wallPos[i]));
	}

	for (int i = 0; i < enemyNum; i++)
	{
		enemyManager->SetEnemy(enemyPos[i]);			//enemyManagerがインスタンスを作成する

	}
}

Stage::~Stage()
{
	delete wallPos;
	delete enemyPos;
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		delete wall[i];

	}
	wall.clear();
	
	delete enemyManager;
}

void Stage::Update()
{
	enemyManager->Update();
}

void Stage::Draw()
{
	ground->Draw();
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		wall[i]->Draw();
	}

	enemyManager->Draw();
}
