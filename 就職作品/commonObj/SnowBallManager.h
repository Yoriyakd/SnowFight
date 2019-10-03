#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include<vector>
#include"SnowBall.h"
class SnowBallManager {
private:
public:
	std::vector <SnowBall*> snowBall;
	SnowBallManager();
	~SnowBallManager();
	void SetSnowBall(SnowBallInitValue *snowBallInitValue);
};
