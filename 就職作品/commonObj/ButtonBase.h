#pragma once
#include"../main.h"
class ButtonBase {
public:
	ButtonBase();
	void Draw();
	void Update();
	bool GetState(void);
protected:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	D3DXVECTOR2 pos, texSize, boxSize;		//���W��button�̃T�C�YX,Y	boxSize�̓N���b�N����̃T�C�Y
	bool nowStae;		//�J�[�\������ɏ�����Ă�����true
};