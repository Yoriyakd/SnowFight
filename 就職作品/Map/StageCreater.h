#pragma once
#include"Ground.h"
#include"../Enemy/Enemy.h"
#include<vector>
class StageCreater {
private:
	static const int stageX = 10;		//マップのサイズの横幅(値は仮のもの)
	static const int stageY = 10;		//マップのサイズの縦幅(値は仮のもの)
	int StageMap[stageX][stageY];		//ステージのオブジェクトの番号を入れてマップを作りたい
	int nowStageNo;						//ステージNo.を参照するときに使う(かもしれない)

	void SetStageMap(int);				//textファイルを開いてマップを作る


public:
	StageCreater();
	~StageCreater();
	void Draw();
};