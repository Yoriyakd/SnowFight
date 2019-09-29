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
	static const int STAGE_X = 11;		//�}�b�v�̃T�C�Y�̉���(�l�͉��̂���)
	static const int STAGE_Y = 11;		//�}�b�v�̃T�C�Y�̏c��(�l�͉��̂���)
	static const float TILE_SIZE;		//�����ŏ������ł��Ȃ�?

	objType StageMap[STAGE_Y][STAGE_X];		//�X�e�[�W�̃I�u�W�F�N�g�̔ԍ������ă}�b�v����肽��		[Y][X]
	int enemyNum, wallNum;				//�X�e�[�W���̃I�u�W�F�N�g�̐�������
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��

	FILE *fp;

	//--------------------------------------------------
	//�t�@�C������ǂݍ��񂾏�񂩂��������W������ϐ�
	D3DXVECTOR3 *wallPos;
	D3DXVECTOR3 *enemyPos;
	//--------------------------------------------------

	std::vector <Wall*> wall;

	EnemyManager *enemyManager;
	Ground *ground;
	Player *player;
	SkyBox *skyBox;

	void SetStageMap(void);				//text�t�@�C�����J���ă}�b�v�����
	void CollisionDetectionS_PtoE(void);



public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
};
