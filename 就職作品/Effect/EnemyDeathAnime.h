#pragma once
#include"../main.h"
class EnemyDeathAnime{
private:
	XFILE mesh;
	D3DXMATRIX startRotMat, mat, rotMat;
	float ang;
	D3DXVECTOR3 RotAxis, SnowBallVec;		//��]�� ��ʂ̐i�s�����x�N�g��
public:
	//�s���XFILE�Ɛ�ʂ̕����x�N�g����n��
	EnemyDeathAnime(D3DXMATRIX, XFILE, D3DXVECTOR3);	
	~EnemyDeathAnime();
	void Draw(void);
	//Anime�I����false��Ԃ�
	bool Update(void);		
};