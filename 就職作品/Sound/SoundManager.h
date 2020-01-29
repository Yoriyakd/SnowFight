#pragma once
#include"../SingletonBase.h"
#include"Sound2D.h"
#include"Sound3D.h"
#include<map>


#define GetSound SoundManager::GetInstance()
class SoundManager : public SingletonBase<SoundManager>{
	friend class SingletonBase<SoundManager>;
public:
	SoundManager();
	~SoundManager();

	//失敗時falseが返る
	bool Play2D(SoundID);

	void AllStop();

	void Initialize();
	void Update();
	
private:
	std::map<SoundID, Sound2D*> Sound2DMap;			//2Dサウンド管理(3Dもここに入れたかったが座標等の設定方法が思いつかなかった)
	std::map<SoundID, Sound3D*> Sound3DMap;			//3Dサウンド管理

	void AllDelete();
};

SoundManager* SingletonBase<SoundManager>::instance = nullptr;