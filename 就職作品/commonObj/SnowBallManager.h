#pragma once
#include"../main.h"
#include<vector>
#include"SnowBall.h"
class SnowBallManager {
private:
public:
	std::vector <SnowBall*> snowBall;
	SnowBallManager();
	~SnowBallManager();
	//��������snowBallInitValue�^���|�C���^�œn��
	void SetSnowBall(SnowBallInitValue *snowBallInitValue);
	void Draw(void);
	void Update(void);
};
