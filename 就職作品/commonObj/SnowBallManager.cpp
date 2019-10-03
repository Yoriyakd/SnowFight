#include "SnowBallManager.h"

SnowBallManager::SnowBallManager()
{
}

SnowBallManager::~SnowBallManager()
{
	for (unsigned int i = 0; i < snowBall.size(); i++)
	{
		delete snowBall[i];
	}
	snowBall.clear();
}

void SnowBallManager::SetSnowBall(SnowBallInitValue *snowBallInitValue)
{
	snowBall.push_back(new SnowBall(*snowBallInitValue));
}
