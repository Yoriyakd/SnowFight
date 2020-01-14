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

	if (ToPlayerAng > ViewingAngle)		//視界から外れるとプレーヤーの方を向きなおす
	{
		return new TurnToPlayer();
	}

	if (ToPlayerAng < -ViewingAngle)	//視界から外れるとプレーヤーの方を向きなおす
	{
		return new TurnToPlayer();
	}

	float Length;
	const float SensingLength = 40.0f;

	Length = D3DXVec3Length(&Enemy.GetPlayerVec());

	if (Length > 25.0f)			//遠いと前にジャンプして距離を詰める
	{
		Enemy.FrontJump();
	}


	if (Length < 15.0f)			//近いと後ろにジャンプして距離を離す
	{
		Enemy.BackJump();
	}

	return nullptr;
}

