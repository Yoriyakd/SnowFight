#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../commonObj/PlayerCamera.h"

class EffectManager {
private:
	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ
	D3DXMATRIX billBoardMat;
public:
	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;

	EffectManager();
	~EffectManager();
	void Draw(void);
	void Update(void);
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);		//playerCamのメソッドにアクセスするためのポインタ
};

extern EffectManager *effectManager;	//mainで宣言
