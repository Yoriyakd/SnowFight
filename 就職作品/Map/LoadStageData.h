#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../Map/MapObjManager.h"
#include"../GameScene/EventManager.h"
#include"../UI/GameObjective.h"


class LoadStageData {
public:
	LoadStageData(int StageNo);
	~LoadStageData();
	
	void SetStageMap(MapObjManager &MapObjManager, EventManager &EventManager, GameObjective &GameObjective, StageBorder &StageBorder);

private:
	int nowStageNo;						//ステージNo.を参照するときに使う
	FILE *fp;
	
};
