#pragma once
#include"../SingletonBase.h"
#include"Sound2D.h"
#include"Sound3D.h"
#include<map>


#define GetSound SoundManager::GetInstance()
class SoundManager : public SingletonBase<SoundManager>{
	friend class SingletonBase<SoundManager>;
public:

	//失敗時falseが返る
	bool Play2D(SoundID _ID);

	void Stop(SoundID _ID);
	void AllStop();

	void Initialize();
	void Update();
	
private:
	SoundManager();
	~SoundManager();
	std::map<SoundID, Sound2D*> Sound2DMap;			//2Dサウンド管理(3Dもここに入れたかったが座標等の設定方法が思いつかなかった)
	std::map<SoundID, Sound3D*> Sound3DMap;			//3Dサウンド管理

	void AllDelete();
};