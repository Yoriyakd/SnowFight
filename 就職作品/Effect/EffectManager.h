#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../Player/PlayerCamera.h"
#include"../SingletonBase.h"


//---------------------------------------------------------------------------------
//�G�t�F�N�g�̃C���X�^���X�������Ă���z��𕡐����N���X
//�}�l�[�W���[�̃C���X�^���X�ɃA�N�Z�X���āA�V�����G�t�F�N�g�����z��ɓ�������
//���V���O���g���N���X
//---------------------------------------------------------------------------------

#define Effect EffectManager::GetInstance()

class EffectManager : public SingletonBase<EffectManager>{
public:
	friend class SingletonBase<EffectManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���

	void AllDelete(void);

	void NewSnowFrag(const D3DXVECTOR3 &Pos);
	void NewSnowLocus(const D3DXMATRIX &SnowBallMat);

	void Draw(void);
	void Update(void);
	void SetBillBoardMat(D3DXMATRIX *BillBoardMat);

private:
	EffectManager();
	~EffectManager();
	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^
	D3DXMATRIX billBoardMat;

	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;
};

EffectManager* SingletonBase<EffectManager>::instance = nullptr;
