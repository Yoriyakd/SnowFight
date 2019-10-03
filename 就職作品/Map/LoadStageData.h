#pragma once
#include<d3dx9.h>
#include<stdio.h>


enum objType { EMPTY, WALL, ENEMY = 5 };

class LoadStageData {
private:
	static const int STAGE_X = 11;		//マップのサイズの横幅(値は仮のもの)
	static const int STAGE_Y = 11;		//マップのサイズの縦幅(値は仮のもの)
	static const float TILE_SIZE;		//ここで初期化できない?

	objType StageMap[STAGE_Y][STAGE_X];		//ステージのオブジェクトの番号を入れてマップを作りたい		[Y][X]
	int enemyNum, wallNum;				//ステージ内のオブジェクトの数を入れる
	int nowStageNo;						//ステージNo.を参照するときに使う

	FILE *fp;

	D3DXVECTOR3 *wallPos;		//将来的に構造体にするかも		座標と壁のタイプ
	D3DXVECTOR3 *enemyPos;		//将来的に構造体にするかも
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
