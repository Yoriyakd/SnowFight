#pragma once
#include"Ground.h"
#include"Wall.h"
#include"../Enemy/Enemy.h"
#include<vector>

enum objType { EMPTY, WALL, ENEMY = 5 };

class Stage {
private:
	static const int STAGE_X = 11;		//マップのサイズの横幅(値は仮のもの)
	static const int STAGE_Y = 11;		//マップのサイズの縦幅(値は仮のもの)
	static const float TILE_SIZE;		//ここで初期化できない?

	objType StageMap[STAGE_Y][STAGE_X];		//ステージのオブジェクトの番号を入れてマップを作りたい		[Y][X]
	int enemyNum, wallNum;				//ステージ内のオブジェクトの数を入れる
	int nowStageNo;						//ステージNo.を参照するときに使う

	FILE *fp;

	D3DXVECTOR3 *wallPos;				
	D3DXVECTOR3 *enemyPos;				

	std::vector <Wall*> wall;
	std::vector <Enemy*> enemy;

	Ground* ground;
	
	void SetStageMap(void);				//textファイルを開いてマップを作る
			


public:
	Stage(int);		//stageNoを入れる
	~Stage();
	void Draw();
};