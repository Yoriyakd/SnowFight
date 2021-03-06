#pragma once
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"StageSelectButton.h"
#include"../Effect/SceneSwitchEffect.h"
#include"../commonObj/Cursor.h"

enum MenuSceneState{IN_MENU, GAME_START, BACK_TO_TITLE_MENU};

class MenuScene : public SceneBase {
public:
	MenuScene();
	~MenuScene();

	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
private:
	void BeginScene(void);			//シーンを開始する際1度だけ呼ぶ		こっちいる？
	void EndScene(void);			//シーンを終了する際1度だけ呼ぶ		デストラクタ前に実行してほしい処理
	bool BackToTitle(void);

	MenuSceneState nowState;
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

	//---------------------------------------
	//ステージセレクト文字
	//---------------------------------------
	LPDIRECT3DTEXTURE9 headCharTex;
	D3DXMATRIX headCharMat;

	//---------------------------------------
	//サンタ服
	//---------------------------------------
	LPDIRECT3DTEXTURE9 SantaWearTex;
	D3DXMATRIX santaWearMat;

	StageSelectButton *stage1Button, *stage2Button;
	int selectedStage;		//選択されたステージ番号
};
