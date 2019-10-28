#pragma once
#include<d3dx9.h>
#include<vector>
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../commonObj/SnowBallManager.h"
#include"../commonObj/PlayerCamera.h"

//���[���h���W�ŊǗ�

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	int remainingBalls;
	float moveSpeed;

	XFILE ballMesh;
	D3DXMATRIX ballMat, ballScalMat;

	StageBorder stageBorder;
	
	PlayerCamera *pPlayerCam;	//�v���C���[�J�����̃|�C���^

	std::vector<D3DXMATRIX> ghostMat;			//��ԋO���̍s��			//�|�C���^�^�Ő錾���Ȃ������瓮���@�Ȃ��H
	LPDIRECT3DTEXTURE9 GhostTex;

	void Move(void);
	//Update�ŌĂ�	�N���b�N�ŋ����o��		������snowBallManager���|�C���^�œn��
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();
	void MakeGhostMat(SnowBallInitValue *snowBallInitValue);
	

public:
	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
	void SetCamera(void);
	void Draw(void);
	int GetRemainingBalls();			//�c�e����Ԃ�
	void SetStageBorder(StageBorder StageBorder);
	D3DXVECTOR3 GetPlayerPos(void);
	void SetPlayerCamPointer(PlayerCamera *PPlayerCam);
};