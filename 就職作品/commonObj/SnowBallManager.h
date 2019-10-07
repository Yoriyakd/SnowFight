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
	//‰Šú‰»‚ÉsnowBallInitValueŒ^‚ğƒ|ƒCƒ“ƒ^‚Å“n‚·
	void SetSnowBall(SnowBallInitValue *snowBallInitValue);
	void Draw(void);
	void Update(void);
};
