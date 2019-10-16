#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"

class EffectManager {
private:
public:
	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;

	EffectManager();
	~EffectManager();
	void Draw(void);
	void Update(void);
	
};

extern EffectManager *effectManager;	//main�Ő錾
