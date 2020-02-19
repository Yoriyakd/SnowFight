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
//ゲーム中の処理を書くクラス
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
	void StartScene();		//シーンを開始する際1度のみ呼ぶ
	void EndScene();		//シーンを終了する際1度のみ呼ぶ
	bool endSceneState;		//シーンが終了中か
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
	//------------------------------------------//クラスにまとめる(設計思いつき次第)
	//リザルト
	//------------------------------------------
	void SwitchResulut();		//ゲームシーンから移行する際呼ぶ
	bool isSwitchResulut;

	int Resultime;

	void StartResult(void);		//リザルトを実行する際1度のみ呼ぶ
	void EndResult(void);		//リザルトを終了する際1度のみ呼ぶ
	bool ResultUpdate(void);

	ResultCam *resultCam;

	bool resultFlag;		//リザルト表示中かの状態
	bool endResultState;	//リザルトが終了中か
	
	LPDIRECT3DTEXTURE9 resultTex, returnTex;
	D3DXMATRIX resultMat, returnMat;

	//------------------------------------------
	//BackToTitle
	//------------------------------------------
	bool BackToTitleFlag;

	void BackToTitle(void);
	//------------------------------------------
	//TimeUpの表示
	//------------------------------------------
	bool TimeUpEffect();
	void PlayTimeUpEffect();
	bool isPlayTimeUpEffect;
	int timeUpEffectCnt;
	const int timeUpEffectPlayTime = 90;
};

extern const float SnowBallGravity;		//☆環境等をまとめたクラスに収めるように変更