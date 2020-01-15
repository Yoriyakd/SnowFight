#include"EngagingMode.h"
#include"../Enemy.h"
#include"TurnToPlayer.h"
#include"ShootSnowBall.h"



EngagingMode::EngagingMode() : ShootCoolTime(180), ViewingAngle(10.0)
{
}

EnemyStateBase *EngagingMode::Action(Enemy &Enemy)
{
	ShootCoolTime--;
	if (ShootCoolTime <= 0)
	{
		return new ShootSnowBall();
	}

	float ToPlayerAng;

	ToPlayerAng = Enemy.CalculateEnemyToPlayerAng();


	if (ToPlayerAng > ViewingAngle)		//���E����O���ƃv���[���[�̕��������Ȃ���
	{
		return new TurnToPlayer();
	}

	if (ToPlayerAng < -ViewingAngle)	//���E����O���ƃv���[���[�̕��������Ȃ���
	{
		return new TurnToPlayer();
	}

	float Length;
	const float SensingLength = 40.0f;

	Length = D3DXVec3Length(&Enemy.GetPlayerVec());

	if (Length > 30.0f)			//�����ƑO�ɃW�����v���ċ������l�߂�
	{
		Enemy.FrontJump();
	}


	if (Length < 15.0f)			//�߂��ƌ��ɃW�����v���ċ����𗣂�
	{
		Enemy.BackJump();
	}

	return nullptr;
}

