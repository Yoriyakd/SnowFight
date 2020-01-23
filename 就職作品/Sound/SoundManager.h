#pragma once
#include"../SingletonBase.h"
#include"Sound2D.h"
#include"Sound3D.h"

#define GetSound SoundManager::GetInstance()
class SoundManager : public SingletonBase<SoundManager>{
	friend class SingletonBase<SoundManager>;
public:
	SoundManager();
	~SoundManager();
	void Play(SoundID);

	void Initialize();
	void Update();
private:
	Sound2D IngameBGM;
};

SoundManager* SingletonBase<SoundManager>::instance = nullptr;