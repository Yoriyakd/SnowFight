#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"

#include"../Player/Player.h"
#include<vector>
#include"../Map/LoadStageData.h"
#include"../Map/Ground.h"

#include"../ResourceManager.h"
#include"../Map/MapObjManager.h"
#include"../Enemy/EnemyManager.h"
#include"../GameScene/SpawnerManager.h"

#include"../commonObj/SkyBox.h"
#include"../Map/Stage1Enclosure.h"
#include"../commonObj/SnowBallManager.h"
#include"../CollisionObserver.h"
#include"../Effect/EffectManager.h"
#include"../Effect/EnemyAnimeManager.h"
#include"EventManager.h"
#include"../Item/DecorationManager.h"

#include"../UI/PickUpInstructions.h"
#include"../UI/RemainingBallUI.h"
#include"../UI/TimeUI.h"
#include"../UI/GameObjective.h"
#include"../Effect/SceneSwitchEffect.h"
#include"ResultCam.h"

//--------------------------------------------------------------------------------------------
//�Q�[�����̏����������N���X
//--------------------------------------------------------------------------------------------


class GameScene : public SceneBase {
public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);

private:
	LoadStageData *loadStageData;
	Ground *ground;
	SkyBox *skyBox;
	Stage1Enclosure *stage1Enclosure;
	SnowBallManager *snowBallManager;
	MapObjManager *mapObjManager;	
	PlayerCamera *playerCam;
	EventManager *eventManager;
	PickUpInstructions *pickUpInstructions;

	StageBorder *stageBorder;
	//------------------------------------------
	//UI
	//------------------------------------------
	RemainingBallUI *remainingBallUI;
	TimeUI *timeUI;
	GameObjective *gameObjective;
	//------------------------------------------//�N���X�ɂ܂Ƃ߂�(�݌v�v��������)
	//���U���g
	//------------------------------------------
	int Resultime;
	bool ResultUpdate(void);

	ResultCam *resultCam;

	bool resultFlag;		//���U���g�\�������̏��
	int sceneSwitchState;		//-1 = �Ó]	0 = �����Ȃ�	1 = ���]
	
	LPDIRECT3DTEXTURE9 resultTex, returnTex;
	D3DXMATRIX resultMat, returnMat;
};

extern const float SnowBallGravity;