#pragma once
#include"Ground.h"
#include"../Enemy/Enemy.h"
#include<vector>
class Stage {
private:
	static const int stageX = 10;		//マップのサイズの横幅(値は仮のもの)
	static const int stageY = 10;		//マップのサイズの縦幅(値は仮のもの)
	int StageMap[stageX][stageY];		//ステージのオブジェクトの番号を入れてマップを作りたい
	int enemyNum, wallNum;				//ステージ内のオブジェクトの数を入れる
	int nowStageNo;						//ステージNo.を参照するときに使う

	FILE *fp;							//オープンしたファイルのポインタ
	

	std::vector <Enemy*> enemy;
	
	void SetStageMap(void);				//textファイルを開いてマップを作る
	
	//charをintに変換　戻り値は変換した数を返す　0～9以外は-999を返す
	int ctoi(char c);					


public:
	Stage(int);		//stageNoを入れる
	~Stage();
	void Draw();
};