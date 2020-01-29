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
	int Resultime;
	bool ResultUpdate(void);

	ResultCam *resultCam;

	bool resultFlag;		//リザルト表示中かの状態
	int sceneSwitchState;		//-1 = 暗転	0 = 動きなし	1 = 明転
	
	LPDIRECT3DTEXTURE9 resultTex, returnTex;
	D3DXMATRIX resultMat, returnMat;
};

extern const float SnowBallGravity;