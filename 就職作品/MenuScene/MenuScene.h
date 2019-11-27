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
	//�؂�ւ��G�t�F�N�g
	//---------------------------------------
	LPDIRECT3DTEXTURE9 switchEffectTex;
	D3DXMATRIX switchEffectMat;
	int sceneSwitchEffectAlpha;
	bool sceneSwitchFlag;

	//---------------------------------------
	//�w�i
	//---------------------------------------
	LPDIRECT3DTEXTURE9 backTex;
	D3DXMATRIX backMat;

	//---------------------------------------
	//�X�e�[�W�Z���N�g�{�[�h
	//---------------------------------------
	LPDIRECT3DTEXTURE9 boardTex;
	D3DXMATRIX boardMat;

	Stage1Button *stage1Button;
};
