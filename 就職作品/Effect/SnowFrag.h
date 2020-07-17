#pragma once
#include"../ResourceManager.h"
class SnowFrag {
private:
	static const int FRAG_NUM = 4;			//飛ばす破片の数
	XFILE mesh;
	D3DXMATRIX fragMat[FRAG_NUM], scalMat[FRAG_NUM], transMat[FRAG_NUM];
	D3DXVECTOR3 fragVec[FRAG_NUM], fragPos[FRAG_NUM];		//飛ぶ方向のベクトル, 座標(ワールド管理)

	LPDIRECT3DTEXTURE9 smokeTex, fragTex;
	VERTEX smokeV[4],fragV[4];
	int alpha;
	D3DXMATRIX smokeBillBoardMat, fragBillBoardMat;
	D3DXMATRIX smokeMat;
	float smokeScaling;

	
public:
	SnowFrag(const D3DXVECTOR3 &Pos);
	~SnowFrag();

	void Draw();
	bool Update();
	void SetBillBoardMat(D3DXMATRIX BillBoardMat);
};