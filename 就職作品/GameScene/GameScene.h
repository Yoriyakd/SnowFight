#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"../Player/Player.h"
#include<vector>
#include"../Map/Ground.h"
#include"../Map/Wall.h"
#include"../Enemy/Enemy.h"
#include"../Enemy/EnemyManager.h"
#include"../commonObj/SkyBox.h"


enum objType { EMPTY, WALL, ENEMY = 5 };

class GameScene : public SceneBase {
private:
	static const int STAGE_X = 11;		//マップのサイズの横幅(値は仮のもの)
	static const int STAGE_Y = 11;		//マップのサイズの縦幅(値は仮のもの)
	static const float TILE_SIZE;		//ここで初期化できない?

	objType StageMap[STAGE_Y][STAGE_X];		//ステージのオブジェクトの番号を入れてマップを作りたい		[Y][X]
	int enemyNum, wallNum;				//ステージ内のオブジェクトの数を入れる
	int nowStageNo;						//ステージNo.を参照するときに使う

	FILE *fp;

	//--------------------------------------------------
	//ファイルから読み込んだ情報から作った座標を入れる変数
	D3DXVECTOR3 *wallPos;
	D3DXVECTOR3 *enemyPos;
	//--------------------------------------------------

	std::vector <Wall*> wall;

	EnemyManager *enemyManager;
	Ground *ground;
	Player *player;
	SkyBox *skyBox;

	void SetStageMap(void);				//textファイルを開いてマップを作る
	void CollisionDetectionS_PtoE(void);



public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
};
