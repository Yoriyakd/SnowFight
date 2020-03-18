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
//ゲーム中の処理を書くクラス
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
	void BeginScene();		//シーンを開始する際1度のみ呼ぶ
	void EndScene();		//シーンを終了する際1度のみ呼ぶ

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

	//------------------------------------------//クラスにまとめる(設計思いつき次第)
	//リザルト
	//------------------------------------------
	void SwitchResult();		//ゲームシーンから移行する際呼ぶ
	int ResulCnt;

	void BeginResult(void);		//リザルトを実行する際1度のみ呼ぶ
	void EndResult(void);		//リザルトを終了する際1度のみ呼ぶ
	bool ResultUpdate(void);

	ResultCam *resultCam;

	LPDIRECT3DTEXTURE9 resultTex, returnTex;
	D3DXMATRIX resultMat, returnMat;

	//------------------------------------------
	//BackToTitle
	//------------------------------------------
	bool BackToTitle(void);
	//------------------------------------------
	//TimeUpの表示
	//------------------------------------------
	void BeginTimeUpEffect();
};

extern const float SnowBallGravity;		//☆環境等をまとめたクラスに収めるように変更
