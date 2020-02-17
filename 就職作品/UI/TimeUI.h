#pragma once
#include"../ResourceManager.h"
#include"../Sound/SoundManager.h"
#include<vector>

class TimeUI {
public:
	TimeUI();
	~TimeUI();
	void Draw();
	void Update();
	void SetTime_s(int setTime_s);		//表示する時間をセットする(秒)
private:
	int displayTime_s;		//表示する時間(秒)

	LPDIRECT3DTEXTURE9 logoTex, numberTex;
	D3DXMATRIX logoMat, numberOffsetMat;
	

	int memoryTime;

	struct BoldNumberData
	{
		int DisplayNum;
		D3DXMATRIX ScalMat;
		int Alpha;			//完全に透明になったら必要なくなる
	};

	std::vector<BoldNumberData*> BoldNumber;		//強調文字を表示したいとき構造体を入れるといい感じに表示してくれるようにする
};