#pragma once
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"Stage1Button.h"
#include"../Effect/SceneSwitchEffect.h"
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
	int sceneSwitchState;		//-1 = 暗転	0 = 動きなし	1 = 明転

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
	int selectedStage;		//選択されたステージ番号
};
