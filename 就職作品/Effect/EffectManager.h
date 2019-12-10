#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../Player/PlayerCamera.h"
#include"EnemyDeathAnime.h"

//---------------------------------------------------------------------------------
//�G�t�F�N�g�̃C���X�^���X�������Ă���z��𕡐����N���X
//�}�l�[�W���[�̃C���X�^���X�ɃA�N�Z�X���āA�V�����G�t�F�N�g�����z��ɓ�������
//---------------------------------------------------------------------------------

class EffectManager {
private:
	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^
	D3DXMATRIX billBoardMat;
public:
	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;
	std::vector<EnemyDeathAnime*> enemyDeathAnime;

	EffectManager();
	~EffectManager();
	void AllDelete(void);
	void Draw(void);
	void Update(void);
	void SetBillBoardMat(D3DXMATRIX *BillBoardMat);
};

extern EffectManager *effectManager;	//main�Ő錾
