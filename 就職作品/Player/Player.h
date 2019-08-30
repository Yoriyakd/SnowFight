#pragma once
#include<d3dx9.h>
#include"../ResourceManager.h"

class Player {
private:
	XFILE mesh;
	D3DXMATRIX mat, transMat, rotMat;
	D3DXVECTOR3 pos;
	static int remainingBalls;
	POINT basePt;
	//============================================================
	//�J�����̕ϐ�
	//============================================================
	float camAngY, camAngX;			//�X���̗ʂ�����	��]���Ŗ��O�t��
	D3DXMATRIX camRotMatY, camRotMatX, camRotMat;

	void Move(void);
	int ShootSnowball(void);

public:
	Player();
	~Player();
	bool Update(void);
	void SetCamera(void);
	void Draw(void);
};