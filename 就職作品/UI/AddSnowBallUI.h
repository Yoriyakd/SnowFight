#pragma once
#include"../ResourceManager.h"
#include"../SingletonBase.h"
#include<vector>

struct AddSnowBallData {
	D3DXMATRIX mat;
	int alpha;
};

class AddSnowBallUI : public SingletonBase<AddSnowBallUI> {
public:
	AddSnowBallUI();
	~AddSnowBallUI();
	void AddSnowBall();		//“üè‚µ‚½ê‡ŒÄ‚Ô(Œ»ó1‚Â‚Ì‚İ’Ç‰Á‚È‚Ì‚Å”‚ğ•Ï‚¦‚éê‡•ÏX‚·‚é)
	void Draw();
	void Update();
private:
	std::vector<AddSnowBallData*> AddUI;
	LPDIRECT3DTEXTURE9 tex;
};