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
#include"../Effect/PlayerHitEffect.h"

#include"../Sound/SoundManager.h"

#include"EventManager.h"
#include"../Item/DecorationManager.h"

#include"../UI/PickUpInstructions.h"
#include"../UI/RemainingBallUI.h"
#include"../UI/TimeUI.h"
#include"../UI/TimePenaltyUI.h"
#include"../UI/GameObjective.h"
#include"../UI/AddSnowBallUI.h"
#include"../Effect/SceneSwitchEffect.h"
#include"../commonObj/BackToTitle.h"
#include"ResultCam.h"

#include"GameTime.h"
#include"TimeUpEffect.h"

//--------------------------------------------------------------------------------------------
//�Q�[�����̏����������N���X
//--------------------------------------------------------------------------------------------

//enum GameSceneState {IN_GAME, SWITCH_RESULT, IN_RESULT, END_RESULT, TIME_UP_EFFECT};

class GameScene : public SceneBase {
public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);

private:
	void BeginScene();		//�V�[�����J�n�����1�x�̂݌Ă�
	void EndScene();		//�V�[�����I�������1�x�̂݌Ă�

	void Collision();


	LoadStageData *loadStageData;
	Ground *ground;
	SkyBox *skyBox;
	Stage1Enclosure *stage1Enclosure;
	MapObjManager *mapObjManager;
	PickUpInstructions *pickUpInstructions;

	static const int EFFECT_CNT = 5;
	PlayerHitEffect *playerHitEffect_Right[EFFECT_CNT];
	PlayerHitEffect *playerHitEffect_Left[EFFECT_CNT];
	PlayerHitEffect *playerHitEffect_Back;

	StageBorder *stageBorder;
	GameSceneState nowState;

	AddUpdateBase *addUpdate;
	//------------------------------------------
	//UI
	//------------------------------------------
	RemainingBallUI *remainingBallUI;
	TimeUI *timeUI;
	std::vector<TimePenaltyUI*> timePenaltyUI;
	GameObjective *gameObjective;

	//------------------------------------------//�N���X�ɂ܂Ƃ߂�(�݌v�v��������)
	//���U���g
	//------------------------------------------
	void SwitchResult();		//�Q�[���V�[������ڍs����یĂ�
	int ResulCnt;

	void BeginResult(void);		//���U���g�����s�����1�x�̂݌Ă�
	void EndResult(void);		//���U���g���I�������1�x�̂݌Ă�
	bool ResultUpdate(void);

	ResultCam *resultCam;

	LPDIRECT3DTEXTURE9 resultTex, returnTex;
	D3DXMATRIX resultMat, returnMat;

	//------------------------------------------
	//BackToTitle
	//------------------------------------------
	bool BackToTitle(void);
	//------------------------------------------
	//TimeUp�̕\��
	//------------------------------------------
	void BeginTimeUpEffect();
};

extern const float SnowBallGravity;		//���������܂Ƃ߂��N���X�Ɏ��߂�悤�ɕύX
