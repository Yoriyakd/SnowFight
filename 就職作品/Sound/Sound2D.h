#pragma once
#include"../ResourceManager.h"
#include<string>

struct SoundInitData {
	SoundID ID;
	bool LoopFlag;			//Loop‚³‚¹‚é‚©true = LoopÄ¶
	int Volume;				//Ä¶‰¹—Ê0`-10,000
	int  MaxPlayCnt;		//“¯‚É‚È‚ç‚¹‚éÅ‘å”(‚±‚Ì”•ª”z—ñ‚ğŠm•Û‚·‚é)
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
	//•Ï”
	//---------------------------------------------------
	SoundInitData soundData;
	LPDIRECTSOUNDBUFFER8 Buffer;
private:

};