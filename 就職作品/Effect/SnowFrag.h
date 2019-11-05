#pragma once
#include"../ResourceManager.h"
class SnowFrag {
private:
	static const int FRAG_NUM = 4;			//��΂��j�Ђ̐�
	XFILE mesh;
	D3DXMATRIX mat[FRAG_NUM], scalMat[FRAG_NUM], transMat[FRAG_NUM];
	D3DXVECTOR3 fragVec[FRAG_NUM], fragPos[FRAG_NUM];		//��ԕ����̃x�N�g��, ���W(���[���h�Ǘ�)
	//int deleteTime;		//������܂ł̃J�E���g

	LPDIRECT3DTEXTURE9 tex;
	VERTEX vertex[4];
	int alpha = 128;
	D3DXMATRIX billBoardMat;
	D3DXMATRIX smokeMat;
	float smokeScaling = 0;

	
public:
	SnowFrag(D3DXVECTOR3 Pos);
	~SnowFrag();

	void Draw();
	bool Update();
	void SetPos(D3DXVECTOR3 Pos);		//��΂����̍��W������
	void SetBillBoardMat(D3DXMATRIX BillBoardMat);
};