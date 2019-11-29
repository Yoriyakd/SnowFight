#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"ArmAnimeBase.h"
#include"ArmRAnimeMid.h"
#include"ThrowRAnime.h"
#include"WindUpRAnime.h"
#include"ArmLWalkAnime.h"
#include"../Item/DecorationManager.h"

//���[���h���W�ŊǗ�

class Player {
public:
	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
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
	//�v���C���[�X�e�[�^�X
	//-----------------------------
	int remainingBalls;		//�c�e��

	bool carryFlag;			//�f�R���[�V�������^��ł��邩
	DecorationID carryDecorationID;		//�^��ł���f�R���[�V�����̓��e

	int HP = 10;
	//-----------------------------
	//��ʓ����֘A
	//-----------------------------
	float timeCnt = 0, shootPowerPCT;
	static const float MaxPowerTime;		//�ő嗭�߂܂łɂ����鎞��

	//-----------------------------
	//�C
	//-----------------------------
	XFILE shoesMesh;
	D3DXMATRIX shoesMat, shoesOffsetMat;

	//-----------------------------
	//�r
	//-----------------------------
	XFILE armRMesh;
	D3DXMATRIX armROffsetMat, armRMat;
	ArmAnimeBase *ArmRAnime;		//�E�r�̃A�j���[�V����

	XFILE armLMesh;
	D3DXMATRIX armLOffsetMat, armLMat;
	ArmAnimeBase *ArmLAnime;		//���r�̃A�j���[�V����


	//-----------------------------
	//�쐬���̐��
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;

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
	//Update�ŌĂ�	�E�N���b�N�ŋ����f�R���[�V�������o��		������snowBallManager���|�C���^�œn��
	void Throw(SnowBallManager *snowBallManager);
	//��ʂ��쐬����	���N���b�N
	void MakeBall();
	//�\�������쐬����
	void MakeGhostMat(ThrowingInitValue *ThrowingInitValue);
	//�ĂԂƖ߂�l�Ő�ʏ������p�̃f�[�^���Ԃ��Ă���
	ThrowingInitValue MakeThrowValue(void);
};