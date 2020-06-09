#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include"../Enemy/Enemy.h"
#include"../commonObj/SnowBall.h"

//-----------------------------------------------------------------------------
//�G�̓����痎���Ă����X�q��V������藎���Ă����A�j���[�V�������Đ�����N���X
//��ʂƓG�̃C���X�^���X��n���Ďg��
//�R���X�g���N�^�[�̑�3������true�̏ꍇHeadShot�p�̃A�j�����Đ�����
//-----------------------------------------------------------------------------

class EnemyHatAnime {
public:
	//��3������true�̏ꍇHeadShot�p�̃A�j�����Đ�����
	EnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot);
	void Draw();
	bool Update();
private:
	XFILE mesh;
	D3DXMATRIX startRotMat, mat, rotMat;
	D3DXVECTOR3 rotAxis, moveVec;
};