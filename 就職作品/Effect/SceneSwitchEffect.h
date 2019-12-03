#pragma once
#include"../ResourceManager.h"
class SceneSwitchEffect {
public:
	SceneSwitchEffect();
	~SceneSwitchEffect();
	void Draw();

	bool ToDarkness(void);
	bool ToBrightness(void);
private:
	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectAlpha;
};

extern SceneSwitchEffect *sceneSwitchEffect;			//main.cpp�Ő錾