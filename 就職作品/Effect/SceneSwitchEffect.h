#pragma once
#include"../ResourceManager.h"

//------------------------------------------------------------------------------------------
//画面を明転暗転させるクラスです。それぞれのメソッドをUpdate内で呼ぶと明転したり暗転します
//ただ、常に明転暗転しようとするため動作の制御は呼び出し側で行ってください
//------------------------------------------------------------------------------------------

class SceneSwitchEffect {
public:
	SceneSwitchEffect();
	~SceneSwitchEffect();
	void Draw();

	bool ToDarkness(void);
	bool ToBrightness(void);
private:
	LPDIRECT3DTEXTURE9 effectTex;
	D3DXMATRIX effectMat;
	int effectAlpha;
};

extern SceneSwitchEffect *sceneSwitchEffect;			//main.cppで宣言