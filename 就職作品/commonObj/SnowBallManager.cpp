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

void SnowBallManager::Draw(void)
{
	for (unsigned int i = 0; i < snowBall.size(); i++)
	{
		snowBall[i]->Draw();
	}
}

void SnowBallManager::Update(void)
{
	for (unsigned int i = 0; i < snowBall.size(); i++)
	{
		if (snowBall[i]->Update() == false)		//Updateがfalseなら
		{
			//SnowFragエフェクト呼ぶ
			effectManager->snowFrag.push_back(new SnowFrag(snowBall[i]->GetPos()));


			//インスタンス削除
			delete snowBall[i];
			snowBall.erase(snowBall.begin() + i);
			i--;
		}
	}
}
