#pragma once
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"StageSelectButton.h"
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
	void StartScene(void);			//�V�[�����J�n�����1�x�����Ă�		����������H
	void EndScene(void);			//�V�[�����I�������1�x�����Ă�		�f�X�g���N�^�O�Ɏ��s���Ăق�������

	bool endSceneState;		//�V�[���̑J�ڃt���O
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

	//---------------------------------------
	//�X�e�[�W�Z���N�g����
	//---------------------------------------
	LPDIRECT3DTEXTURE9 headCharTex;
	D3DXMATRIX headCharMat;

	//---------------------------------------
	//�J�[�\��
	//---------------------------------------
	LPDIRECT3DTEXTURE9 cursorTex;
	D3DXMATRIX cursorMat;


	//---------------------------------------
	//�T���^��
	//---------------------------------------
	LPDIRECT3DTEXTURE9 SantaWearTex;
	D3DXMATRIX santaWearMat;

	StageSelectButton *stage1Button, *stage2Button;
	int selectedStage;		//�I�����ꂽ�X�e�[�W�ԍ�
};
