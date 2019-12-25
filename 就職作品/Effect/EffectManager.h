#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../Player/PlayerCamera.h"


//---------------------------------------------------------------------------------
//�G�t�F�N�g�̃C���X�^���X�������Ă���z��𕡐����N���X
//�}�l�[�W���[�̃C���X�^���X�ɃA�N�Z�X���āA�V�����G�t�F�N�g�����z��ɓ�������
//---------------------------------------------------------------------------------

class EffectManager {
public:
	EffectManager();
	~EffectManager();
	void AllDelete(void);

	void NewSnowFrag(const D3DXVECTOR3 &Pos);
	void NewSnowLocus(const D3DXMATRIX &SnowBallMat);

	void Draw(void);
	void Update(void);
	void SetBillBoardMat(D3DXMATRIX *BillBoardMat);

private:
	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^
	D3DXMATRIX billBoardMat;

	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;
};

extern EffectManager *effectManager;	//main�Ő錾
