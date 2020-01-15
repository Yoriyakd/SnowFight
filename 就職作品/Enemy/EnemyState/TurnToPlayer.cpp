#include "TurnToPlayer.h"
#include"EngagingMode.h"
#include"../Enemy.h"

EnemyStateBase * TurnToPlayer::Action(Enemy & Enemy)
{
	float Ang;

	Ang = Enemy.CalculateEnemyToPlayerAng();

	if (-5 <= Ang && Ang <= 5)
	{
		Enemy.Spin(Ang);
		return new EngagingMode();				//��]���I��������ԑJ��
	}

	if (Ang <= 0)
	{
		Enemy.Spin(-5);		//5�x����]
	}
	else
	{
		Enemy.Spin(5);
	}
	
	return nullptr;
}
