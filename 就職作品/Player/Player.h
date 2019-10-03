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
	static int remainingBalls;
	float moveSpeed;
	

	//============================================================
	//�J�����̕ϐ�
	//============================================================
	static const float camHight;
	POINT basePt;

	PlayerCamera *playerCam;
	//------------------------------------------------------------

	void Move(void);
	int ShootSnowball(SnowBallManager *snowBallManager);

	

public:
	//std::vector <SnowBall*> snowBall_P;

	Player();
	~Player();
	bool Update(SnowBallManager *snowBallManager);
	void SetCamera(void);
	void Draw(void);
};