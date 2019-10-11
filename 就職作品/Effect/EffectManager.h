#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"../Effect/SnowFrag.h"

class EffectManager {
private:
public:
	std::vector<SnowFrag*> snowFrag;

	EffectManager();
	~EffectManager();
	void Draw(void);
	void Update(void);
	
};

extern EffectManager *effectManager;	//main�Ő錾
