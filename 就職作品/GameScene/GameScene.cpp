#include "GameScene.h"





const float GameScene::TILE_SIZE = 6.0f;				//�錾���������ł��Ȃ��̂ł����ŏ�����



void GameScene::SetStageMap(void)
{
	char FileName[16];
	//=================================================================================
	//�t�@�C���I�[�v��
	//=================================================================================

	sprintf_s(FileName, sizeof(FileName), "Map/stage%d.txt", nowStageNo);		//�t�@�C���p�X�쐬

	fopen_s(&fp, FileName, "r");	//fopen�̃Z�L�����e�B�����ł炵��


	//=================================================================================
	//�ǂݎ�����l���Z�b�g
	//=================================================================================
	fscanf_s(fp, "��:%d\n", &wallNum);
	fscanf_s(fp, "�G:%d\n", &enemyNum);
	fscanf_s(fp, "map\n");					//��ǂ�

	for (int i = 0; i < STAGE_Y; i++)
	{
		for (int j = 0; j < STAGE_X; j++)
		{
			fscanf_s(fp, "%1d ", &StageMap[i][j]);
		}
		fscanf_s(fp, "\n");					//��ǂ�
	}

	fclose(fp);

	wallPos = new D3DXVECTOR3[wallNum];
	enemyPos = new D3DXVECTOR3[enemyNum];			//���I�m�ۂ���

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

			EMPTY:					//�������Ȃ�
				break;
			}
		}
	}
}

void GameScene::CollisionDetectionS_PtoE(void)
{
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < player->snowBall_P.size(); j++)
		{
			D3DXVECTOR3 EnemyPosTmp = enemyManager->enemy[i]->GetPos(), SnowBall_PPosTmp = player->snowBall_P[j]->GetPos();

			if (CollisionDetection(EnemyPosTmp, 3, SnowBall_PPosTmp, 1.5))		//���a���Ƃŕϐ���
			{
				delete enemyManager->enemy[i];
				delete player->snowBall_P[j];
				player->snowBall_P.erase(player->snowBall_P.begin() + j);
				enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
				j--;
				i--;
			}

		}
	}
}

GameScene::GameScene(int StageNo)
{
	player = new Player();
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
		enemyManager->SetEnemy(enemyPos[i]);			//enemyManager���C���X�^���X���쐬����

	}
}

GameScene::~GameScene()
{
	delete player;
	delete wallPos;
	delete enemyPos;
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		delete wall[i];

	}
	wall.clear();

	delete enemyManager;
}

void GameScene::Render3D(void)
{
	ground->Draw();
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		wall[i]->Draw();
	}

	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		enemyManager->enemy[i]->Draw();
	}
	player->Draw();

}

void GameScene::SetCamera(void)
{
	player->SetCamera();
}

void GameScene::Render2D(void)
{
}

bool GameScene::Update()
{
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		enemyManager->enemy[i]->Update();
	}
	player->Update();
	
	CollisionDetectionS_PtoE();
	return true;
}
