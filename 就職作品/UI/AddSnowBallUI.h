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
	void AddSnowBall();		//���肵���ꍇ�Ă�(����1�̂ݒǉ��Ȃ̂Ő���ς���ꍇ�ύX����)
	void Draw();
	void Update();
private:
	std::vector<AddSnowBallData*> AddUI;
	LPDIRECT3DTEXTURE9 tex;
};