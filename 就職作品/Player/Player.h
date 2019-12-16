#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"ArmAnimeBase.h"
#include"ArmAnimeMid.h"
#include"ThrowAnime.h"
#include"WindUpAnime.h"
#include"MakeSnowBallAnime.h"
#include"../Item/DecorationManager.h"
#include"../UI/PickUpInstructions.h"

//���[���h���W�ŊǗ�

class Player {
public:
	Player();
	~Player();
	bool Update(SnowBallManager &SnowBallManager, DecorationManager &DecorationManager, PickUpInstructions &PickUpInstructions);
	void SetCamera(void);
	void Draw(void);

	int GetRemainingBalls();			//�c�e����Ԃ�
	D3DXVECTOR3 GetPlayerPos(void);
	void GetCollisionSphere(CollisionSphere *CollisionSphere);
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);

	void HitSnowBall();
	int GetHP();

private:
	D3DXMATRIX transMat, rotMatY, rotMatX;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, -2.0f, 0.0f);		//�J�����̈ʒu����̋���

	//-----------------------------
	//�v���C���[�X�e�[�^�X		������ύX���Ē�������
	//-----------------------------
	const int StartBallCnt = 10;	//�X�^�[�g���̃{�[���̐�
	const float MakeTime = 1.5;		//�쐬�ɕK�v�Ȏ���
	const float MaxPowerTime = 1.5f;	//�ő嗭�߂܂łɂ����鎞��
	int HP = 10;


	//-----------------------------
	//�X�e�[�^�X�ϐ�
	//-----------------------------
	int remainingBalls;		//�c�e��

	bool carryFlag;			//�f�R���[�V�������^��ł��邩
	DecorationID carryDecorationID;		//�^��ł���f�R���[�V�����̓��e
	
	//-----------------------------
	//��ʓ����֘A
	//-----------------------------
	float timeCnt = 0, shootPowerPCT;

	//-----------------------------
	//�C
	//-----------------------------
	XFILE shoesMesh;
	D3DXMATRIX shoesMat, shoesOffsetMat, shoesRotMatX;
	float shoesAngX;

	//-----------------------------
	//�r
	//-----------------------------
	XFILE armRMesh;
	D3DXMATRIX armROffsetMat, armRMat;

	XFILE armLMesh;
	D3DXMATRIX armLOffsetMat, armLMat;

	ArmAnimeBase *ArmAnime;		//�r�̃A�j���[�V����


	//-----------------------------
	//�쐬���̐��
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;

	const float MaxBallScal = 1.5;			//�쐬���̐�ʂ̍ő�T�C�Y

	//-----------------------------
	//�����蔻��
	//-----------------------------
	float CollisionRadius = 1.0f;		//�������蔻��̔��a

	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^

	std::vector<D3DXMATRIX> ghostMat;			//��ԋO���̍s��
	LPDIRECT3DTEXTURE9 GhostTex;

	

	//-----------------------------
	//private���\�b�h
	//-----------------------------
	//Update�ŌĂ�	���N���b�N�ŋ����f�R���[�V�������o��		������snowBallManager���|�C���^�œn��
	void Throw(SnowBallManager &snowBallManager, DecorationManager &decorationManager);
	//��ʂ��쐬����	�E�N���b�N
	void MakeBall();
	//�C�̐�ʍ쐬���̃A�j���[�V����
	void ShoesMakeBallAnime(bool AnimeState);
	//�\�������쐬����
	void MakeGhostMat(ThrowingInitValue *ThrowingInitValue);
	//�ĂԂƖ߂�l�Ő�ʏ������p�̃f�[�^���Ԃ��Ă���
	ThrowingInitValue MakeThrowValue(void);
};