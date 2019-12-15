#pragma once
#include<d3dx9.h>
#include"../main.h"
#include"../ResourceManager.h"
#include"../Effect/EffectManager.h"
class SnowBall {
private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat, transMat;
	D3DXVECTOR3 moveVec, memoryPos, globalMoveVec;
	int deleteTime;
	ID id;
	const float Sphereadius = 0.4f;				//�����蔻��Ɏg�����̔��a
public:
	SnowBall(ThrowingInitValue, ID);			//���ˈʒu�A���ˊp�x�A���˕����A���˃p���[
	~SnowBall();
	bool Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos();
	D3DXMATRIX GetMat();
	D3DXVECTOR3 GetMoveVec();				//�O���[�o���̈ړ��x�N�g����n��
	ID GetID();
	void GetCollisionSphere(CollisionSphere *CollisionSphere);
};