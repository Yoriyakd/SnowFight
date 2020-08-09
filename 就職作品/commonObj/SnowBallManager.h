#pragma once
#include"../main.h"
#include<vector>
#include"SnowBall.h"
#include"../Effect/EffectManager.h"
//------------------------------------------------------------------------
//雪玉のインスタンスを持つクラス
//------------------------------------------------------------------------

class GameScene;

class SnowBallManager{
	friend class GameScene;			//GameSceneのみインスタンス作成削除は許可
public:
	std::vector <SnowBall*> snowBall;	
	//全インスタンス削除
	void AllDelete(void);
	//消したいインスタンスの配列番号を渡すとそのインスタンスを削除する
	void DeleteInstance(unsigned int ite);
	//初期化にsnowBallInitValue型をポインタで渡す
	void CreateSnowBall(ThrowingInitValue *ThrowingInitValue, ID _ID);
	void Draw(void);
	void Update(void);
private:
	SnowBallManager();
	~SnowBallManager();
};