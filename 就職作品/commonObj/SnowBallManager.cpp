#include "SnowBallManager.h"

SnowBallManager::SnowBallManager()
{
}

SnowBallManager::~SnowBallManager()
{
	AllDelete();
}

void SnowBallManager::AllDelete(void)
{
	for (auto *SnowBall : snowBall)
	{
		delete SnowBall;
	}
	snowBall.clear();
}

void SnowBallManager::DeleteInstance(unsigned int ite)
{
	delete snowBall[ite];
	snowBall.erase(snowBall.begin() + ite);
}

void SnowBallManager::SetSnowBall(ThrowingInitValue *ThrowingInitValue, ID _ID)
{
	snowBall.push_back(new SnowBall(*ThrowingInitValue, _ID));
}

void SnowBallManager::Draw(void)
{
	for (auto *SnowBall : snowBall)
	{
		SnowBall->Draw();
	}
}

void SnowBallManager::Update(void)
{
	for (unsigned int i = 0; i < snowBall.size(); i++)
	{
		if (snowBall[i]->Update() == false)		//Update��false�Ȃ�
		{
			//SnowFrag�G�t�F�N�g�Ă�
			effectManager->NewSnowFrag(snowBall[i]->GetPos());


			//�C���X�^���X�폜
			DeleteInstance(i);
			i--;
		}
	}
}
