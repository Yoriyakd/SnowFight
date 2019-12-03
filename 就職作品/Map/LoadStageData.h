#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../Map/MapObjManager.h"
#include"../GameScene/EventManager.h"


class LoadStageData {
public:
	LoadStageData(int StageNo);
	~LoadStageData();
	void GetStageSize(float *StageSizeX, float *StageSizeZ);
	void SetStageMap(MapObjManager *MapObjManager, EventManager *EventManager);

private:
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��
	float stageSizeX, stageSizeZ;		//�ǂݍ��񂾃X�e�[�W�̃T�C�Y��ۑ�

	FILE *fp;
	
};
