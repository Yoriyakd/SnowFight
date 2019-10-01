#pragma once
#include"../main.h"
#include"../ResourceManager.h"
class StageFence {
private:
	XFILE mesh;
	D3DXMATRIX mat;
public:
	StageFence(void);
	~StageFence();
	void SetMat(D3DXVECTOR3 Pos);
	void SetMat(D3DXVECTOR3 Pos, float Ang);
	void Draw(void);
};
