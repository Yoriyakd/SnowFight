#pragma once
#include"../ResourceManager.h"

//------------------------------------------------------------------------
//PlayerがHITしたときに表示するエフェクトのクラス
//Initializeメソッドを呼んで初期化してから使う
//------------------------------------------------------------------------

//どの方向からあたった時に表示するものかを表す
enum HitEffectID
{
	Right,
	Left,
	Back
};

class PlayerHitEffect{
public:
	PlayerHitEffect();
	~PlayerHitEffect();
	void Initialize_BackEffect();
	void Initialize_RightEffect();
	void Initialize_LeftEffect();
	//表示させる状態にする
	void Active();
	//今表示されているかの状態を取得する
	bool GetActiveState();

	void Draw();
	void Update();
	//Playerがどの方向から飛んできた雪玉に当たったか計算するメソッド
	static HitEffectID CalculateHitDirection(const D3DXVECTOR3 &SnowBallVec);
private:
	//表示する座標を決める際に呼ぶ呼ぶとIDで決められた範囲でランダムな座標がセットされる
	void InitPos();

	LPDIRECT3DTEXTURE9 tex;
	RECT rect;
	D3DXMATRIX transMat;
	D3DXVECTOR3 pos;
	HitEffectID id;
	int alpha;
	static const int DISPLAY_TIME = 60;		//薄くしない時間(フレーム単位)
	int displayCnt;
	bool activeFlag;
};