#pragma once
#include"../ResourceManager.h"

//------------------------------------------------------------------------------------------
//��ʂ𖾓]�Ó]������N���X�ł��B���ꂼ��̃��\�b�h��Update���ŌĂԂƖ��]������Ó]���܂�
//�����A��ɖ��]�Ó]���悤�Ƃ��邽�ߓ���̐���͌Ăяo�����ōs���Ă�������
//------------------------------------------------------------------------------------------

class SceneSwitchEffect {
public:
	SceneSwitchEffect();
	~SceneSwitchEffect();
	void Draw();

	bool ToDarkness(void);
	bool ToBrightness(void);
private:
	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectAlpha;
};

extern SceneSwitchEffect *sceneSwitchEffect;			//main.cpp�Ő錾