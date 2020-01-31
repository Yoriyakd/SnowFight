#pragma once
#include"../commonObj/ButtonBase.h"

class StageSelectButton : public ButtonBase {
public:
	StageSelectButton();
	~StageSelectButton();
	void Stage1Initialize(void);				//�Ƃ肠���������ɏ���(text��CSV����ǂݍ��ނ悤�ɕύX����)��
	void Stage2Initialize(void);

	void Draw();
protected:
	void OnMouseEvent(void);		//�}�E�X����ɏ���Ă���Ƃ��̏���
	void OffMouseEvent(void);		//�}�E�X����ɏ���Ă��Ȃ��Ƃ��̏���
private:

	LPDIRECT3DTEXTURE9 stagePicTex, backTex, stageTextTex, stageNumTex;
	D3DXMATRIX mat, textOffsetMat, numOffsetMat, picOffsetMat;

	int stageNum;
	int onMouseColor;
};