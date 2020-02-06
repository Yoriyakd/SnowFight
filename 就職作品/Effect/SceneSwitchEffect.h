#pragma once
#include"../ResourceManager.h"
#include"../SingletonBase.h"

//------------------------------------------------------------------------------------------
//��ʂ𖾓]�Ó]������N���X�ł��B���ꂼ��̃��\�b�h��Update���ŌĂԂƖ��]������Ó]���܂�
//�����A��ɖ��]�Ó]���悤�Ƃ��邽�ߓ���̐���͌Ăяo�����ōs���Ă�������
//���V���O���g���N���X
//------------------------------------------------------------------------------------------

#define GetSceneSwitchEffect SceneSwitchEffect::GetInstance()
enum SwitchEffectState { FADE_IN, STOP, FADE_OUT};

class SceneSwitchEffect : public SingletonBase<SceneSwitchEffect>{
public:
	friend class SingletonBase<SceneSwitchEffect>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���

	void Draw();

	void Update();

	void PlayFadeIn(void);
	void PlayFadeOut(void);

	SwitchEffectState GetFadeState();
	
private:
	SceneSwitchEffect();
	~SceneSwitchEffect();

	void ToDarkness(void);
	void ToBrightness(void);

	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectAlpha;
	bool switchFlag;		//��ʂ��Â��Ȃ�V�[���ύX�̏������ł������Ƃ�\��
	SwitchEffectState nowState;
};
SceneSwitchEffect* SingletonBase<SceneSwitchEffect>::instance = nullptr;