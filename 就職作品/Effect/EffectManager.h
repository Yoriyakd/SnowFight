#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../commonObj/PlayerCamera.h"

class EffectManager {
private:
	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^
	D3DXMATRIX billBoardMat;
public:
	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;

	EffectManager();
	~EffectManager();
	void Draw(void);
	void Update(void);
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);		//playerCam�̃��\�b�h�ɃA�N�Z�X���邽�߂̃|�C���^
};

extern EffectManager *effectManager;	//main�Ő錾
