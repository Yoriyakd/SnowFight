#include "SetStageData.h"

const float SetStageData::TILE_SIZE = 18.0f;				//�錾���������ł��Ȃ��̂ł����ŏ�����

//===============================================
//private
//===============================================

void SetStageData::SetStageMap(void)
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
