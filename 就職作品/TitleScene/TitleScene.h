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
	void BeginScene(void);			//�V�[�����J�n�����1�x�����Ă�
	void EndScene(void);			//�V�[�����I�������1�x�����Ă�

	LPDIRECT3DTEXTURE9 logoTex, kyeInstructionTex;
	D3DXMATRIX logoMat, kyeInstructionMat;
	const int logoTexX = 832, kyeInstructionX = 426;		//���S��x�����̃T�C�Y	x�����g������ꉞx�����ϐ��ɂ��Ă݂�

	LPDIRECT3DTEXTURE9 switchEffectTex;
	D3DXMATRIX switchEffectMat;
	int sceneSwitchEffectAlpha;
	bool endSceneState;
	
	bool ESCFlag;	//�Q�[���I����ESC�������ςȂ�����
	bool isClick;	//�������ςȂ��΍�

	LPDIRECT3DTEXTURE9 backTex;
	D3DXMATRIX backMat;
};
