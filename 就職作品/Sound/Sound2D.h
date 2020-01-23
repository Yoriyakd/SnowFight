#pragma once
#include"../ResourceManager.h"
class Sound2D {
public:
	Sound2D();
	virtual ~Sound2D();
	void Play();
	void Stop();
	void Initialize();
	void Update();
	bool IsPlaying();
protected:
	//---------------------------------------------------
	//ïœêî
	//---------------------------------------------------
	LPDIRECTSOUNDBUFFER8 Buffer;
	int volume;
	bool loopFrag;
	SoundID ID;		//
private:
	void IsPlayeEnd();

};