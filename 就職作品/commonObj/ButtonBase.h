#pragma once
#include"../main.h"
#include"../ResourceManager.h"

struct ButtonData {
	D3DXVECTOR2 Pos;		//座標
	D3DXVECTOR2 BoxSize;	//クリック判定のサイズ
};

class ButtonBase {
public:
	ButtonBase(void);
	void Draw();
	void Update();
	bool GetState(void);
protected:
	virtual void OnMouseEvent(void);
	virtual void OffMouseEvent(void);
	
	ButtonData buttonData;
	bool nowStae;		//カーソルが上に乗っかていたらtrue
	
};