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
	void StartScene();		//�V�[�����J�n�����1�x�̂݌Ă�
	void EndScene();		//�V�[�����I�������1�x�̂݌Ă�
	bool endSceneState;		//�V�[�����I������
	bool isESCKye;

	LoadStageData *loadStageData;
	Ground *ground;
	SkyBox *skyBox;
	Stage1Enclosure *stage1Enclosure;
	MapObjManager *mapObjManager;	
	EventManager *eventManager;
	PickUpInstructions *pickUpInstructions;

	static const int EFFECT_CNT = 5;
	PlayerHitEffect *playerHitEffect_Right[EFFECT_CNT];
	PlayerHitEffect *playerHitEffect_Left[EFFECT_CNT];
	PlayerHitEffect *playerHitEffect_Back;

	StageBorder *stageBorder;
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
	void SwitchResulut();		//�Q�[���V�[������ڍs����یĂ�
	bool isSwitchResulut;

	int Resultime;

	void StartResult(void);		//���U���g�����s�����1�x�̂݌Ă�
	void EndResult(void);		//���U���g���I�������1�x�̂݌Ă�
	bool ResultUpdate(void);

	ResultCam *resultCam;

	bool resultFlag;		//���U���g�\�������̏��
	bool endResultState;	//���U���g���I������
	
	LPDIRECT3DTEXTURE9 resultTex, returnTex;
	D3DXMATRIX resultMat, returnMat;

	//------------------------------------------
	//BackToTitle
	//------------------------------------------
	bool BackToTitleFlag;

	void BackToTitle(void);
	//------------------------------------------
	//TimeUp�̕\��
	//------------------------------------------
	bool TimeUpEffect();
	void PlayTimeUpEffect();
	bool isPlayTimeUpEffect;
	int timeUpEffectCnt;
	const int timeUpEffectPlayTime = 90;
};

extern const float SnowBallGravity;		//���������܂Ƃ߂��N���X�Ɏ��߂�悤�ɕύX