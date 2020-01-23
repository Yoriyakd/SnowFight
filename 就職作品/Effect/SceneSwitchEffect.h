#pragma once
#include"../ResourceManager.h"
#include"../SingletonBase.h"

//------------------------------------------------------------------------------------------
//画面を明転暗転させるクラスです。それぞれのメソッドをUpdate内で呼ぶと明転したり暗転します
//ただ、常に明転暗転しようとするため動作の制御は呼び出し側で行ってください
//※シングルトンクラス
//------------------------------------------------------------------------------------------

#define GetSceneSwitchEffect SceneSwitchEffect::GetInstance()

class SceneSwitchEffect : public SingletonBase<SceneSwitchEffect>{
public:
	friend class SingletonBase<SceneSwitchEffect>;			//SingletonBaseでのインスタンス作成削除は許可

	void Draw();

	bool ToDarkness(void);
	bool ToBrightness(void);
private:
	SceneSwitchEffect();
	~SceneSwitchEffect();
	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectAlpha;
};
SceneSwitchEffect* SingletonBase<SceneSwitchEffect>::instance = nullptr;