#include"EngagingMode.h"
#include"../Enemy.h"
#include"TurnToPlayer.h"



EngagingMode::EngagingMode() : ViewingAngle(10.0)
{
}

EnemyStateBase *EngagingMode::Action(Enemy &Enemy)
{
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

	if (Length > 25.0f)			//�����ƑO�ɃW�����v���ċ������l�߂�
	{
		Enemy.FrontJump();
	}


	if (Length < 15.0f)			//�߂��ƌ��ɃW�����v���ċ����𗣂�
	{
		Enemy.BackJump();
	}

	return nullptr;
}

