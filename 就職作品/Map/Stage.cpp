#include "Stage.h"

Ground* ground;


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
	
	//fopen�̎��s�Ƃ��t�@�C���̏������ԈႦ�����m�ł��Ȃ��ǂ��Ȃ�

	int dataBuff[256];
	int i = 0;

	while (dataBuff[i] == EOF)
	{ 
		 ctoi(fgetc(fp));		//���ʂ�0�`9����Ȃ��������΂��Ď��ɍs������������
		dataBuff[i];
	}

	//while (1)
	//{
	//	int buf;
	//	
	//	buf = fgetc(fp);
	//	if (buf == EOF)break;
	//	if (buf >= '0' && buf <= '9')		//�����ȊO�͂���
	//	{
	//		enemyNum = buf - '0';			//�����R�[�h�𐔎��ɕϊ�
	//		break;
	//	}


	//}

	//while (1)
	//{
	//	int buf;

	//	buf = fgetc(fp);
	//	if (buf == EOF)break;
	//	if (buf >= '0' && buf <= '9')		//�����ȊO�͂���
	//	{
	//		wallNum = buf - '0';			//�����R�[�h�𐔎��ɕϊ�
	//		break;
	//	}


	//}

	//while (1)
	//{
	//	int buf;

	//	buf = fgetc(fp);
	//	if (buf == EOF)break;
	//	if (buf >= '0' && buf <= '9')		//�����ȊO�͂���
	//	{
	//		for (int i = 0; i < stageY; i++)
	//		{
	//			for (int j = 0; j < stageX; j++)	//���ꂶ��_���S���ɓ����̂�����@��񂢂ꂽ�甲���Ȃ���
	//			{
	//				StageMap[j][i] = buf - '0';			//�����R�[�h�𐔎��ɕϊ�   
	//			}
	//		}
	//		
	//	}


	//}
}

int Stage::ctoi(char c)
{

	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	return -999;

	
}


//===============================================
//public
//===============================================



Stage::Stage(int stageNo)
{
	nowStageNo = stageNo;
	SetStageMap();
	ground = new Ground;			//�摜�̓ǂݍ��݂�������
	enemy.push_back(new Enemy);
}

Stage::~Stage()
{
	fclose(fp);
}

void Stage::Draw()
{
	ground->Draw();
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw();
	}
}
