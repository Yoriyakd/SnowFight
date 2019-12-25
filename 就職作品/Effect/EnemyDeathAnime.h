#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../Enemy/Enemy.h"

//-------------------------------------------------------------------------
//�|��Ă���G��V�������|���A�j���[�V�������Đ�����N���X
//��ʂƓG�̃C���X�^���X��n���Ďg��
//-------------------------------------------------------------------------

class EnemyDeathAnime{
public:
	//�s���XFILE�Ɛ�ʂ̕����x�N�g����n��
	EnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall);
	~EnemyDeathAnime();
	void Draw(void);
	//Anime�I����false��Ԃ�
	bool Update(void);
private:
	XFILE mesh;
	D3DXMATRIX startMat, mat, rotMat;
	float nowAng;
	D3DXVECTOR3 rotAxis;		//��]��
};