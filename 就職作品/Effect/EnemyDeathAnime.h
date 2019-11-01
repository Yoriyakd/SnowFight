#pragma once
#include"../main.h"
class EnemyDeathAnime{
private:
	XFILE mesh;
	D3DXMATRIX startMat, mat, rotMat;
	float ang;
	D3DXVECTOR3 RotAxis, SnowBallVec;		//回転軸
public:
	//行列とXFILEと雪玉の方向ベクトルを渡す
	EnemyDeathAnime(D3DXMATRIX, XFILE, D3DXVECTOR3);	
	~EnemyDeathAnime();
	void Draw(void);
	//Anime終了でfalseを返す
	bool Update(void);		
};