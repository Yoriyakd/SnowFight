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
	int nowStageNo;						//ステージNo.を参照するときに使う
	float stageSizeX, stageSizeZ;		//読み込んだステージのサイズを保存

	FILE *fp;
	void SetStageMap(void);
};
