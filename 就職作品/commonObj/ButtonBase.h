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
	D3DXVECTOR2 pos, texSize, boxSize;		//座標とbuttonのサイズX,Y	boxSizeはクリック判定のサイズ
	bool nowStae;		//カーソルが上に乗っかていたらtrue
};