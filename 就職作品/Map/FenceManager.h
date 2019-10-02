#pragma once
#include<vector>
#include"../Map/StageFence.h"

struct FenceData {
	int cntX;
	int cntZ;
	float offSetX;
	float offSetZ;
};

class FenceManager{
private:
	const float blockInterval = 15.0;
	float stageSizeX, stageSizeZ;
	std::vector<StageFence*> stageFence;
	FenceData fenceData;
public:
	

	FenceManager(int CntX, int CntZ, float OffSetX, float OffSetZ);
	~FenceManager();
	void SetFence();
	void Draw(void);
	void SetStageSize(float, float);
};