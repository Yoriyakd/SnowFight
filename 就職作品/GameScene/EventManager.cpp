#include "EventManager.h"

EventManager::EventManager()
{
	wavePatternBase = new WavePattern1();
}

EventManager::~EventManager()
{
	delete wavePatternBase;
}

void EventManager::Update()
{
	wavePatternBase->WaveProcessing();
}
