#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"../Effect/SceneSwitchEffect.h"

class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();

	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);

private:
	void BeginScene(void);			//シーンを開始する際1度だけ呼ぶ
	void EndScene(void);			//シーンを終了する際1度だけ呼ぶ

	LPDIRECT3DTEXTURE9 logoTex, kyeInstructionTex;
	D3DXMATRIX logoMat, kyeInstructionMat;
	const int logoTexX = 832, kyeInstructionX = 426;		//ロゴのx方向のサイズ	xだけ使うから一応xだけ変数にしてみた

	LPDIRECT3DTEXTURE9 switchEffectTex;
	D3DXMATRIX switchEffectMat;
	int sceneSwitchEffectAlpha;
	bool endSceneState;
	
	bool ESCFlag;	//ゲーム終了のESC押しっぱなし判定
	bool isClick;	//押しっぱなし対策

	LPDIRECT3DTEXTURE9 backTex;
	D3DXMATRIX backMat;
};
