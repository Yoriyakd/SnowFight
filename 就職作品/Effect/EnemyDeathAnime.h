#pragma once
#include"../main.h"
class EnemyDeathAnime{
private:
	XFILE mesh;
	D3DXMATRIX startMat, mat, rotMat;
	float ang;
	D3DXVECTOR3 RotAxis, SnowBallVec;		//��]��
public:
	//�s���XFILE�Ɛ�ʂ̕����x�N�g����n��
	EnemyDeathAnime(D3DXMATRIX, XFILE, D3DXVECTOR3);	
	~EnemyDeathAnime();
	void Draw(void);
	//Anime�I����false��Ԃ�
	bool Update(void);		
};