#include "ShootSnowBall.h"
#include"EngagingMode.h"
#include"../Enemy.h"

const float ShootSnowBall::ANIME_SPEED = 0.05f;

ShootSnowBall::ShootSnowBall()
{
	//�U�肩�Ԃ�A�j���[�V�����̏I���̍s����쐬�i���񏉊������Ă�̔���������l���Ȃ��Ɓj
	D3DXMATRIX TmpMat;
	D3DXMatrixRotationZ(&TmpMat, D3DXToRadian(45));		//�X�����̊p�x

	D3DXVECTOR3 RotAxis(0, 1, 0);
	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &TmpMat);
	D3DXMatrixRotationAxis(&windUpEndMat ,&RotAxis, D3DXToRadian(5));		//�U�肩�Ԃ�p�x

	D3DXMatrixRotationAxis(&throwEndMat ,&RotAxis, D3DXToRadian(-5));		//�ӂ蔲���p�x

	D3DXMatrixIdentity(&windUpStartMat);
	D3DXMatrixIdentity(&throwStartMat);
	windUpAnimeFrame = 0;
	throwAnimeFrame = 0;
}


EnemyStateBase* ShootSnowBall::Action(Enemy& Enemy)
{
	if (Enemy.IsJump() == false)		//�W�����v���͌����Ȃ�
	{
		//�U�肩�Ԃ�
		if (!WindUpAnime(Enemy))return nullptr;		//�I���܂ōs��
		if (!ThrowAnime(Enemy))return nullptr;
		Enemy.ShootSnowBall();
		
		return new EngagingMode();
	}
	return nullptr;
}

bool ShootSnowBall::WindUpAnime(Enemy& Enemy)
{
	if (windUpAnimeFrame >= 1)
	{
		windUpAnimeFrame = 1;
		return true;		//�������I�������true��Ԃ�
	}

	QuaternionAnime(&nowMat, &nowMat, &windUpStartMat, &windUpEndMat, windUpAnimeFrame);
	windUpAnimeFrame += ANIME_SPEED;
	

	D3DXMATRIX TmpMat;

	TmpMat = Enemy.GetMat();

	TmpMat = nowMat * TmpMat;

	Enemy.SetMat(TmpMat);


	return false;
}

bool ShootSnowBall::ThrowAnime(Enemy& Enemy)
{
	if (throwAnimeFrame >= 1)
	{
		throwAnimeFrame = 1;
		return true;		//�������I�������true��Ԃ�
	}

	//�����ŐႾ��܂��X������ǉ�
	QuaternionAnime(&nowMat, &nowMat, &throwStartMat, &throwEndMat, throwAnimeFrame);
	throwAnimeFrame += ANIME_SPEED;


	D3DXMATRIX TmpMat;

	TmpMat = Enemy.GetMat();

	TmpMat = nowMat * TmpMat;

	Enemy.SetMat(TmpMat);
	return false;
}

