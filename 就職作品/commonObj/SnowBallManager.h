#pragma once
#include"../main.h"
#include<vector>
#include"SnowBall.h"
#include"../Effect/EffectManager.h"
#include"../SingletonBase.h"
//------------------------------------------------------------------------
//雪玉のインスタンスを持つクラス
//※シングルトンクラス
//------------------------------------------------------------------------

#define GetSnowBallManager SnowBallManager::GetInstance()

class SnowBallManager : public SingletonBase<SnowBallManager>{
	friend class SingletonBase<SnowBallManager>;			//SingletonBaseでのインスタンス作成削除は許可
public:
	std::vector <SnowBall*> snowBall;	
	//全インスタンス削除
	void AllDelete(void);
	//消したいインスタンスの配列番号を渡すとそのインスタンスを削除する
	void DeleteInstance(unsigned int ite);
	//初期化にsnowBallInitValue型をポインタで渡す
	void SetSnowBall(ThrowingInitValue *ThrowingInitValue, ID _ID);
	void Draw(void);
	void Update(void);
private:
	SnowBallManager();
	~SnowBallManager();
};