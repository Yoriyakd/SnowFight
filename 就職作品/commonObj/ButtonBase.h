#pragma once
#include"../main.h"
class ButtonBase {
public:
	void Draw();
	bool CheckState(void);
protected:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	D3DXVECTOR2 pos, size;		//���W��button�̃T�C�YX,Y
};