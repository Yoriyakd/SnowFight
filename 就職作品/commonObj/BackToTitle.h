#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"BackToTitleButton.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../Sound/SoundManager.h"
#include"../commonObj/Cursor.h"

//--------------------------------------------------------------
//�^�C�g���o�b�N�m�F��ʂ̃N���X
//CallBackToTitle���\�b�h���Ăі߂�l��false�Ȃ�V�[�����؂�ւ��(���Ăяo������Update��false��Ԃ����Ƃ��킷��Ȃ��悤��)
//���V���O���g��
//--------------------------------------------------------------

enum RETURN_STATE { RETURN_TITLE, CANCEL, WAITING_INPUT, NOT_ACTIVE };

#define GetBackToTitle BackToTitle::GetInstance()
class BackToTitle : public SingletonBase<BackToTitle> {
	friend class SingletonBase<BackToTitle>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:

	void Draw();
	RETURN_STATE CallBackToTitle();		//�߂�l�@-1 = No, 0 = �I���Ȃ���ʌp�� 1 = Yes �V�[���؂�ւ�

private:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;

	bool nowState;			//�Ăяo����Ă��邩��\��
	bool isESCKey;

	BackToTitleButton *YesButton;
	BackToTitleButton *NoButton;
	BackToTitle();
	~BackToTitle();
};

BackToTitle* SingletonBase<BackToTitle>::instance = nullptr;		//nullptr�ŏ�����