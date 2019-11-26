#pragma once
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
class MenuScene : public SceneBase {
public:
	MenuScene();
	~MenuScene();

	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
private:
	bool stageSelectFlag;

	LPDIRECT3DTEXTURE9 switchEffectTex;
	D3DXMATRIX switchEffectMat;
	int sceneSwitchEffectAlpha;
	bool sceneSwitchFlag;

	D3DXMATRIX RightArrowMat, LeftArrowMat;
	D3DXVECTOR3 RightArrowPos, LeftArrowPos;
};
