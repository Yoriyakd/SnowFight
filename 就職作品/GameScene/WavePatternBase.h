#pragma once
class WavePatternBase {
public:
	virtual WavePatternBase* WaveProcessing(void) = 0;
protected:
	int waveLimit, nowWaveTime;
private:
};
