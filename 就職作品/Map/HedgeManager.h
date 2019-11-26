#pragma once
#include<vector>
#include"StageHedge.h"


class HedgeManager{
public:
	HedgeManager(StageBorder * StageBorder);
	~HedgeManager();
	void Draw(void);


private:
	const float blockInterval = 15.0;
	
	std::vector<StageHedge*> stageHedge;

	StageBorder stageBorder;
};