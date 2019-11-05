#pragma once
#include"../ResourceManager.h"
class SnowFrag {
private:
	static const int FRAG_NUM = 4;			//飛ばす破片の数
	XFILE mesh;
	D3DXMATRIX mat[FRAG_NUM], scalMat[FRAG_NUM], transMat[FRAG_NUM];
	D3DXVECTOR3 fragVec[FRAG_NUM], fragPos[FRAG_NUM];		//飛ぶ方向のベクトル, 座標(ワールド管理)
	//int deleteTime;		//消えるまでのカウント

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
	void SetPos(D3DXVECTOR3 Pos);		//飛ばす元の座標を入れる
	void SetBillBoardMat(D3DXMATRIX BillBoardMat);
};