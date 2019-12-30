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
	D3DXVECTOR2 pos, texSize, boxSize;		//座標とbuttonのサイズX,Y	boxSizeはクリック判定のサイズ
	bool nowStae;		//カーソルが上に乗っかていたらtrue
};