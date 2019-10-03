#pragma once
#include<d3dx9.h>
#include<stdio.h>


enum objType { EMPTY, WALL, ENEMY = 5 };

class LoadStageData {
private:
	static const int STAGE_X = 11;		//�}�b�v�̃T�C�Y�̉���(�l�͉��̂���)
	static const int STAGE_Y = 11;		//�}�b�v�̃T�C�Y�̏c��(�l�͉��̂���)
	static const float TILE_SIZE;		//�����ŏ������ł��Ȃ�?

	objType StageMap[STAGE_Y][STAGE_X];		//�X�e�[�W�̃I�u�W�F�N�g�̔ԍ������ă}�b�v����肽��		[Y][X]
	int enemyNum, wallNum;				//�X�e�[�W���̃I�u�W�F�N�g�̐�������
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��

	FILE *fp;

	D3DXVECTOR3 *wallPos;		//�����I�ɍ\���̂ɂ��邩��		���W�ƕǂ̃^�C�v
	D3DXVECTOR3 *enemyPos;		//�����I�ɍ\���̂ɂ��邩��
	void SetStageMap(void);
public:
	LoadStageData(int StageNo);
	~LoadStageData();

	int GetWallNum();
	int GetEnemyNum();
	D3DXVECTOR3 GetWallData(int);
	D3DXVECTOR3 GetEnemyData(int);
	void GetStageSize(float*, float*);
};
