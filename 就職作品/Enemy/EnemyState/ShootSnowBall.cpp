#include "ShootSnowBall.h"
#include"EngagingMode.h"
#include"../Enemy.h"

EnemyStateBase* ShootSnowBall::Action(Enemy& Enemy)
{
	if (Enemy.IsJump() == false)		//�W�����v���͌����Ȃ�
	{
		//�U�肩�Ԃ�
		if (!WindUp(Enemy))return nullptr;		//�I���܂ōs��
		Enemy.ShootSnowBall();
		return new EngagingMode();
	}
	return nullptr;
}

bool ShootSnowBall::WindUp(Enemy& Enemy)
{
	//�����ŐႾ��܂��X������ǉ�
	return true;		//�������I�������true��Ԃ�
	return false;
}

