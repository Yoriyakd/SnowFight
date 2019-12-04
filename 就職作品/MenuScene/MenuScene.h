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
	//�؂�ւ��G�t�F�N�g
	//---------------------------------------
	int sceneSwitchState;		//-1 = �Ó]	0 = �����Ȃ�	1 = ���]

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

	Stage1Button *stage1Button;
	int selectedStage;		//�I�����ꂽ�X�e�[�W�ԍ�
};
