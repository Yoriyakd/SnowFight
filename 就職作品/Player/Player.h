#pragma once
#include<d3dx9.h>
#include<vector>
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"PlayerStateBase.h"
#include"PlayerStateIdle.h"
#include"ThrowState.h"
#include"WindUpState.h"
#include"MakeSnowBallState.h"
#include"../Item/DecorationManager.h"
#include"../UI/PickUpInstructions.h"
#include"../UI/AddSnowBallUI.h"
#include"CarryItem.h"

#define GetPlayer Player::GetInstance()

//------------------------------------------------------------------------
//player�̃N���X
//�J�����̈ʒu�Ƀ��f����\������B������󂯕t���Đ�ʂ𓊂���B�c�e����HP�̃X�e�[�^�X�ێ�
//��剻���Ă���̂Ń��t�@�N�^�����O�̕K�v������
//------------------------------------------------------------------------

//���[���h���W�ŊǗ�

class Player : public SingletonBase<Player>{
	friend class SingletonBase<Player>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	bool Update(PickUpInstructions &PickUpInstructions);
	void Draw(void);

	int GetRemainingBalls();			//�c�e����Ԃ�
	const D3DXVECTOR3 GetPlayerPos(void);
	const D3DXMATRIX GetMat(void);
	void GetCollisionSphere(CollisionSphere *CollisionSphere);

	void Throw(const float PowerPCT);

	bool IsThrowAnything();
	void SetShootPower(float ShootPower);

	//��ʂ��쐬����	�E�N���b�N
	void MakeBallStart();
	//��ʂ����I���ۂ̏���
	void MakeBallEnd();

	bool CanMakeSnowBall();
private: 
	Player();
	~Player();

	D3DXMATRIX transMat, rotMatY, rotMatX;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, -2.0f, 0.0f);		//�J�����̈ʒu����̋���

	//-----------------------------
	//�v���C���[�X�e�[�^�X		������ύX���Ē�������
	//-----------------------------
	const int StartBallCnt = 10;	//�X�^�[�g���̃{�[���̐�
	const float MakeTime = 1.5;		//�쐬�ɕK�v�Ȏ���
	const int AddShootAng = 25;		//��ʂ��΂��ۃJ�����̊p�x�̂ǂꂭ�炢��ɔ�΂����̊p�x

	//-----------------------------
	//�X�e�[�^�X�ϐ�
	//-----------------------------
	int remainingBalls;		//�c�e��
	float shootPower;

	bool carryFlag;			//�f�R���[�V�������^��ł��邩
	CarryObjectID carryObjID;		//�^��ł���f�R���[�V�����̓��e
	
	//-----------------------------
	//��ʓ����֘A
	//-----------------------------

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

	PlayerStateBase *playerState;		//�r�̃A�j���[�V����


	//-----------------------------
	//�쐬���̐��
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;

	const float MaxBallScal = 1.5;			//�쐬���̐�ʂ̍ő�T�C�Y
	float makingTimeCnt;
	bool canMakeSnowBallFlag;

	//-----------------------------
	//�ێ����Ă����ʁA�f�R���[�V�����̕\��
	//-----------------------------
	CarryItem* carryItem;

	//-----------------------------
	//�����蔻��
	//-----------------------------
	float CollisionRadius = 1.0f;		//�������蔻��̔��a


	std::vector<D3DXMATRIX> ghostMat;			//��ԋO���̍s��
	LPDIRECT3DTEXTURE9 ghost_SnowTex, ghost_DecoTex;

	//-----------------------------
	//private���\�b�h
	//-----------------------------
	
	//�C�̐�ʍ쐬���̃A�j���[�V����
	void ShoesMakeBallAnime(bool AnimeState);
	//�\�������쐬����
	void MakeGhostMat();
	//�ĂԂƖ߂�l�Ő�ʏ������p�̃f�[�^���Ԃ��Ă���
	ThrowingInitValue MakeThrowValue(const float PowerPct);
};

Player* SingletonBase<Player>::instance = nullptr;