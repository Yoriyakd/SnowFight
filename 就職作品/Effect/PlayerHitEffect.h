#pragma once
#include"../ResourceManager.h"


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
	void Active();

	bool GetActiveState();

	void Draw();
	void Update();
	static void CalculateHitDirection(const D3DXVECTOR3 &SnowBallVec);
private:
	void InitPos();

	LPDIRECT3DTEXTURE9 tex;
	RECT rect;
	D3DXMATRIX transMat;
	D3DXVECTOR3 pos;
	HitEffectID id;
	int alpha;
	static const int DISPLAY_TIME = 60;
	int displayCnt;
	bool activeFlag;
};