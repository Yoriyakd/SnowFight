#pragma once
#include"../main.h"
#include"../ResourceManager.h"
//��ʂ̋O��		�f�U�C�����Ђǂ��̂ŗp�ύX
class SnowLocus{
private:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	VERTEX vertex[4];
	int alpha = 255;
public:
	SnowLocus(D3DXMATRIX SnowBallMat);
	~SnowLocus();
	void SetMat(D3DXMATRIX SnowBallMat);		//��ʂ̍s���n��	����Ȃ�����
	void Draw();
	bool Update();
};
