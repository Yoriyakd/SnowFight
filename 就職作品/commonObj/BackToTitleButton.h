#pragma once
#include"ButtonBase.h"
#include"../ResourceManager.h"
class BackToTitleButton : public ButtonBase {
public:
	void Draw();
	void Initialize(ButtonData &_ButtonData, LPDIRECT3DTEXTURE9 _Tex);
private:
	D3DXMATRIX mat;
	LPDIRECT3DTEXTURE9 tex;
};