#include "EventManager.h"

EventManager::EventManager()
{
	wavePattern = new WavePattern1();
}

EventManager::~EventManager()
{
	delete wavePattern;
}

void EventManager::Update()
{
	if (wavePattern != nullptr)
	{
		WavePatternBase *NextPattern;
		NextPattern = wavePattern->WaveProcessing();
		if (NextPattern != nullptr)
		{
			delete wavePattern;
			wavePattern = NextPattern;
		}
	}
	
}
