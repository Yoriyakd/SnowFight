#include "Stage.h"


const float Stage:: TILE_SIZE = 6.0f;				//�錾���������ł��Ȃ��̂ł����ŏ�����

//===============================================
//private
//===============================================

void Stage::SetStageMap(void)
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

	//int a;
	//fscanf(fp, "��:%d\n", &a);		//�V�[�N�ʒu�͓ǂ񂾂��ƈړ�����
	//fscanf(fp, "%d ", &a);

//	int b[10] = {0,1,2,3,4,5};
//	fwrite(b, sizeof(b), 1, fp);		�o�C�i���^���ł���K�v������
//	fread(b, sizeof(b), 1, fp);			�o�C�i���^����

	
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
		enemyManager->SetEnemy(enemyPos[i]);			//enemyManager���C���X�^���X���쐬����

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
