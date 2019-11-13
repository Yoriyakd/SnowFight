#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"PlayerCamera.h"
#include"ArmRAnimeBase.h"
#include"ArmRAnimeMid.h"
#include"ArmRAnimeFront.h"

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
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);

private:
	D3DXMATRIX transMat, rotMatY, rotMatX;
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 shootOffset = D3DXVECTOR3(2.0f, -2.0f, 0.0f);		//�J�����̈ʒu����̋���
	int remainingBalls;		//�c�e��
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
	XFILE armMeshR;
	D3DXMATRIX armOffsetMatR, armRotMatXR, armMatR;
	ArmRAnimeBase *ArmRAnime;

	//-----------------------------
	//�쐬���̐��
	//-----------------------------
	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat, ballOffsetMat;


	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^

	std::vector<D3DXMATRIX> ghostMat;			//��ԋO���̍s��			//�|�C���^�^�Ő錾���Ȃ������瓮���@�Ȃ��H
	LPDIRECT3DTEXTURE9 GhostTex;

	//-----------------------------
	//private���\�b�h
	//-----------------------------
	//Update�ŌĂ�	�N���b�N�ŋ����o��		������snowBallManager���|�C���^�œn��
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();
	void MakeGhostMat(SnowBallInitValue *snowBallInitValue);
	//�ĂԂƖ߂�l�Ő�ʏ������p�̃f�[�^���Ԃ��Ă���
	SnowBallInitValue MakeSnowBallInitValue(void);
};