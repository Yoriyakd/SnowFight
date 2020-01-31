#pragma once
#include"../commonObj/ButtonBase.h"

class StageSelectButton : public ButtonBase {
public:
	StageSelectButton();
	~StageSelectButton();
	void Stage1Initialize(void);				//とりあえずここに書く(textやCSVから読み込むように変更する)☆
	void Stage2Initialize(void);

	void Draw();
protected:
	void OnMouseEvent(void);		//マウスが上に乗っているときの処理
	void OffMouseEvent(void);		//マウスが上に乗っていないときの処理
private:

	LPDIRECT3DTEXTURE9 stagePicTex, backTex, stageTextTex, stageNumTex;
	D3DXMATRIX mat, textOffsetMat, numOffsetMat, picOffsetMat;

	int stageNum;
	int onMouseColor;
};