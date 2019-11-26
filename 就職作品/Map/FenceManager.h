#pragma once
#include<vector>
#include"../Map/StageFence.h"


class FenceManager{
public:
	FenceManager(StageBorder * StageBorder);
	~FenceManager();
	void Draw(void);


private:
	const float blockInterval = 15.0;
	
	std::vector<StageFence*> stageFence;

	StageBorder stageBorder;
};