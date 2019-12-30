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

	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	D3DXVECTOR2 pos, texSize, boxSize;		//���W��button�̃T�C�YX,Y	boxSize�̓N���b�N����̃T�C�Y
	bool nowStae;		//�J�[�\������ɏ�����Ă�����true
};