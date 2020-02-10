#pragma once
#include"../ResourceManager.h"
#include<vector>

class TimeUI {
public:
	TimeUI();
	~TimeUI();
	void Draw();
	void Update();
	void SetTime_s(int setTime_s);		//�\�����鎞�Ԃ��Z�b�g����(�b)
private:
	int displayTime_s;		//�\�����鎞��(�b)

	LPDIRECT3DTEXTURE9 logoTex, numberTex;
	D3DXMATRIX logoMat, numberOffsetMat;
	
	struct BoldNumberData
	{
		int DisplayNum;
		D3DXMATRIX ScalMat;
		float Alpha;			//���S�ɓ����ɂȂ�����K�v�Ȃ��Ȃ�
	};

	std::vector<BoldNumberData*> BoldNumber;		//����������\���������Ƃ��\���̂�����Ƃ��������ɕ\�����Ă����悤�ɂ���
};