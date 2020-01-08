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
	D3DXVECTOR2 pos, boxSize;		//���W��button�̃T�C�YX,Y	boxSize�̓N���b�N����̃T�C�Y
	bool nowStae;		//�J�[�\������ɏ�����Ă�����true
	int stageNum;
	int onMouseColor;
};