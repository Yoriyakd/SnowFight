#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"ButtonBase.h"
#include"../SceanSwitcher/SceneSwitcher.h"

//--------------------------------------------------------------
//�^�C�g���o�b�N�m�F��ʂ̃N���X
//CallBackToTitle���\�b�h���Ăі߂�l��false�Ȃ�V�[�����؂�ւ��(���Ăяo������Update��false��Ԃ����Ƃ��킷��Ȃ��悤��)
//���V���O���g��
//--------------------------------------------------------------

#define GetBackToTitle BackToTitle::GetInstance()
class BackToTitle : public SingletonBase<BackToTitle> {
	friend class SingletonBase<ResourceManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	BackToTitle();
	~BackToTitle();

	void Draw();
	int CallBackToTitle();		//�߂�l�@-1 = No, 0 = �I���Ȃ���ʌp�� 1 = Yes �V�[���؂�ւ�

	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;

	bool calledState;			//�Ăяo����Ă��邩��\��

	ButtonBase *YesButton;
	ButtonBase *NoButton;
};

BackToTitle* SingletonBase<BackToTitle>::instance = nullptr;		//nullptr�ŏ�����