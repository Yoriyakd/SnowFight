#pragma once
#include"../SingletonBase.h"
#include"Direct3D.h"

class Sprite : public SingletonBase<Sprite>
{
	friend SingletonBase<Sprite>;
public:
	const LPD3DXSPRITE& GetSprite(void);

private:
	Sprite(void);
	~Sprite();

	void CreateSprite(void);

	// スプライト
	LPD3DXSPRITE lpSprite;

private:
};