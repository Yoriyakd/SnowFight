#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../Player/PlayerCamera.h"
#include"../SingletonBase.h"


//---------------------------------------------------------------------------------
//エフェクトのインスタンスが入っている配列を複数持つクラス
//マネージャーのインスタンスにアクセスして、新しいエフェクトを作り配列に入れる役割
//※シングルトンクラス
//---------------------------------------------------------------------------------

#define Effect EffectManager::GetInstance()

class EffectManager : public SingletonBase<EffectManager>{
public:
	friend class SingletonBase<EffectManager>;			//SingletonBaseでのインスタンス作成削除は許可

	void AllDelete(void);

	void NewSnowFrag(const D3DXVECTOR3 &Pos);
	void NewSnowLocus(const D3DXMATRIX &SnowBallMat);

	void Draw(void);
	void Update(void);
	void SetBillBoardMat(D3DXMATRIX *BillBoardMat);

private:
	EffectManager();
	~EffectManager();
	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ
	D3DXMATRIX billBoardMat;

	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;
};

EffectManager* SingletonBase<EffectManager>::instance = nullptr;
