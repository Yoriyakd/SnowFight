#include "Stage.h"

Ground* ground;

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

	int enemyIte = 0;

	//printf_s("%d", &wallNum);

	for (int i = 0; i < STAGE_Y; i++)
	{
		for (int j = 0; j < STAGE_X; j++)
		{
			switch (StageMap[i][j])
			{
			case WALL:				//�ǂ͌��
				break;

			case ENEMY:
				enemyPos[enemyIte] = D3DXVECTOR3((float)((STAGE_X - j) * TILE_SIZE), 0, (float)((STAGE_Y - i) * TILE_SIZE));
				enemyIte++;
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
