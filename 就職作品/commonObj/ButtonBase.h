#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class ButtonBase {
public:
	ButtonBase(int Stage);
	void Draw();
	void Update();
	bool GetState(void);
protected:
	void Stage1Initialize(void);
	void Stage2Initialize(void);

	LPDIRECT3DTEXTURE9 stagePicTex, backTex, stageTextTex, stageNumTex;
	D3DXMATRIX mat, textOffsetMat, numOffsetMat, picOffsetMat;
	D3DXVECTOR2 pos, boxSize;		//座標とbuttonのサイズX,Y	boxSizeはクリック判定のサイズ
	bool nowStae;		//カーソルが上に乗っかていたらtrue
	int stageNum;
	int onMouseColor;
};