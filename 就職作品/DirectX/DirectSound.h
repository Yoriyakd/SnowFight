#pragma once
#include"../SingletonBase.h"
#include<dsound.h>
#include "../Sound/wavread.h"
#pragma comment(lib, "dsound.lib")

class DirectSound : public SingletonBase<DirectSound>{
	friend class SingletonBase<DirectSound>;
public:
	//DirectSound������
	bool InitDirectSound(void);

	//�T�E���h�������Ă���
	const LPDIRECTSOUND8& GetLpDSound(void);

private:
	//�O���ŃC���X�^���X���֎~
	DirectSound();
	~DirectSound();

	//�T�E���h
	LPDIRECTSOUND8 lpDSound = nullptr;

	//�v���C�}���o�b�t�@
	LPDIRECTSOUNDBUFFER lpSPrimary = nullptr;
};