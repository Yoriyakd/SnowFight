#pragma once
#include"../ResourceManager.h"
#include<string>

struct SoundInitData {
	SoundID ID;
	bool LoopFlag;			//Loop�����邩true = Loop�Đ�
	int Volume;				//�Đ�����0�`-10,000
	int  MaxPlayCnt;		//�����ɂȂ点��ő吔(���̐����z����m�ۂ���)
	std::string FileName;
};

class Sound2D {
public:
	Sound2D();
	virtual ~Sound2D();
	void Initialize(const SoundInitData& _SoundInitData);

	void Play();
	void Stop();

	bool IsPlaying();
	int GetMaxPlayCnt(void);
protected:
	//---------------------------------------------------
	//�ϐ�
	//---------------------------------------------------
	SoundInitData soundData;
	LPDIRECTSOUNDBUFFER8 Buffer;
private:

};