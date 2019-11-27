#pragma once
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"Stage1Button.h"
class MenuScene : public SceneBase {
public:
	MenuScene();
	~MenuScene();

	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
private:
	//---------------------------------------
	//切り替えエフェクト
	//---------------------------------------
	LPDIRECT3DTEXTURE9 switchEffectTex;
	D3DXMATRIX switchEffectMat;
	int sceneSwitchEffectAlpha;
	bool sceneSwitchFlag;

	//---------------------------------------
	//背景
	//---------------------------------------
	LPDIRECT3DTEXTURE9 backTex;
	D3DXMATRIX backMat;

	//---------------------------------------
	//ステージセレクトボード
	//---------------------------------------
	LPDIRECT3DTEXTURE9 boardTex;
	D3DXMATRIX boardMat;

	Stage1Button *stage1Button;
};
