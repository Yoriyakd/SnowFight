#pragma once
#include"../ResourceManager.h"
class SceneBase
{
private:
	DWORD NTlmt, BTlmt, NTcnt, BTcnt;
	int cntFPS;

public:
	virtual ~SceneBase();
	virtual bool Update(void);
	virtual void Render3D(void);
	virtual void Render2D(void);
	virtual void SetCamera(void);
	void Frame(void);
};