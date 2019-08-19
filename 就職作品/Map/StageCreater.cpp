#include "StageCreater.h"

Ground *ground;

//===============================================
//private
//===============================================

void StageCreater::SetStageMap(int stageNo)
{

}

//===============================================
//public
//===============================================

StageCreater::StageCreater(int)
{
	ground = new Ground;
}

StageCreater::~StageCreater()
{
}

void StageCreater::Draw()
{
	ground->Draw();
}
