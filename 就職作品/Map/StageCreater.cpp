#include "StageCreater.h"

Ground* ground;
std::vector <Enemy*> enemy;

//===============================================
//private
//===============================================

void StageCreater::SetStageMap(int stageNo)
{

}

//===============================================
//public
//===============================================

StageCreater::StageCreater()
{
	ground = new Ground;			//‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚ª‚¨‚à‚¢
	enemy.push_back(new Enemy);
}

StageCreater::~StageCreater()
{
}

void StageCreater::Draw()
{
	ground->Draw();
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw();
	}
}
