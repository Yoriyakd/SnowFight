#pragma once
#include<d3dx9.h>
#include<stdio.h>


enum objType { EMPTY, WALL, ENEMY = 5 };

class LoadStageData {
public:
	LoadStageData(int StageNo);
	~LoadStageData();
	void GetStageSize(float *StageSizeX, float *StageSizeZ);

private:
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��
	float stageSizeX, stageSizeZ;		//�ǂݍ��񂾃X�e�[�W�̃T�C�Y��ۑ�

	FILE *fp;
	void SetStageMap(void);
};
