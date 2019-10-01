#pragma once
#include<vector>
#include"../Map/StageFence.h"
//#include"../GameScene/GameScene.h"

class FenceManager{
private:
	const float blockSize = 15.0;
	float StageSizeX, StageSizeY;
public:
	std::vector<StageFence*> stageFence;
	FenceManager();
	FenceManager(int CntX, int CntZ, float OffSetX, float OffSetZ);
	~FenceManager();
	void Draw(void);
};