#pragma once
#include"../ResourceManager.h"
#include"../SingletonBase.h"

//------------------------------------------------------------------------------------------
//��ʂ𖾓]�Ó]������N���X�ł��B���ꂼ��̃��\�b�h��Update���ŌĂԂƖ��]������Ó]���܂�
//�����A��ɖ��]�Ó]���悤�Ƃ��邽�ߓ���̐���͌Ăяo�����ōs���Ă�������
//���V���O���g���N���X
//------------------------------------------------------------------------------------------

#define GetSceneSwitchEffect SceneSwitchEffect::GetInstance()

class SceneSwitchEffect : public SingletonBase<SceneSwitchEffect>{
public:
	friend class SingletonBase<SceneSwitchEffect>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���

	void Draw();

	bool ToDarkness(void);
	bool ToBrightness(void);
private:
	SceneSwitchEffect();
	~SceneSwitchEffect();
	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectAlpha;
};
SceneSwitchEffect* SingletonBase<SceneSwitchEffect>::instance = nullptr;