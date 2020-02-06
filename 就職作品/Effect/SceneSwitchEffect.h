#pragma once
#include"../ResourceManager.h"
#include"../SingletonBase.h"

//------------------------------------------------------------------------------------------
//画面を明転暗転させるクラスです。それぞれのメソッドをUpdate内で呼ぶと明転したり暗転します
//ただ、常に明転暗転しようとするため動作の制御は呼び出し側で行ってください
//※シングルトンクラス
//------------------------------------------------------------------------------------------

#define GetSceneSwitchEffect SceneSwitchEffect::GetInstance()
enum SwitchEffectState { FADE_IN, STOP, FADE_OUT};

class SceneSwitchEffect : public SingletonBase<SceneSwitchEffect>{
public:
	friend class SingletonBase<SceneSwitchEffect>;			//SingletonBaseでのインスタンス作成削除は許可

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
	bool switchFlag;		//画面が暗くなりシーン変更の準備ができたことを表す
	SwitchEffectState nowState;
};
SceneSwitchEffect* SingletonBase<SceneSwitchEffect>::instance = nullptr;