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
	

	//============================================================
	//�J�����̕ϐ�
	//============================================================
	static const float camHight;

	PlayerCamera *playerCam;
	//------------------------------------------------------------

	void Move(void);
	//Update�ŌĂ�	�N���b�N�ŋ����o��		������snowBallManager���|�C���^�œn��
	void ShootSnowball(SnowBallManager *snowBallManager);

	void MakeBall();

	

public:
	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
	void SetCamera(void);
	void Draw(void);
	int GetRemainingBalls();			//�c�e����Ԃ�
	void SetStageBorder(StageBorder StageBorder);
};