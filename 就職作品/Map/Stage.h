#pragma once
#include"Ground.h"
#include"Wall.h"
#include"../Enemy/Enemy.h"
#include<vector>

enum objType { EMPTY, WALL, ENEMY = 5 };

class Stage {
private:
	static const int STAGE_X = 11;		//�}�b�v�̃T�C�Y�̉���(�l�͉��̂���)
	static const int STAGE_Y = 11;		//�}�b�v�̃T�C�Y�̏c��(�l�͉��̂���)
	static const float TILE_SIZE;		//�����ŏ������ł��Ȃ�?

	objType StageMap[STAGE_Y][STAGE_X];		//�X�e�[�W�̃I�u�W�F�N�g�̔ԍ������ă}�b�v����肽��		[Y][X]
	int enemyNum, wallNum;				//�X�e�[�W���̃I�u�W�F�N�g�̐�������
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��

	FILE *fp;

	D3DXVECTOR3 *wallPos;				
	D3DXVECTOR3 *enemyPos;				

	std::vector <Wall*> wall;
	std::vector <Enemy*> enemy;

	Ground* ground;
	
	void SetStageMap(void);				//text�t�@�C�����J���ă}�b�v�����
			


public:
	Stage(int);		//stageNo������
	~Stage();
	void Draw();
};