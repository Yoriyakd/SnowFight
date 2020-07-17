#pragma once
#include"../SingletonBase.h"
#include<dsound.h>
#include "../Sound/wavread.h"
#pragma comment(lib, "dsound.lib")

class DirectSound : public SingletonBase<DirectSound>{
	friend class SingletonBase<DirectSound>;
public:
	//DirectSound初期化
	bool InitDirectSound(void);

	//サウンドを持ってくる
	const LPDIRECTSOUND8& GetLpDSound(void);

private:
	//外部でインスタンス化禁止
	DirectSound();
	~DirectSound();

	//サウンド
	LPDIRECTSOUND8 lpDSound = nullptr;

	//プライマリバッファ
	LPDIRECTSOUNDBUFFER lpSPrimary = nullptr;
};