#pragma once
#include"../main.h"
class Kamakura {
public:
	Kamakura();
	~Kamakura();
	void SetPos(D3DXVECTOR3 Pos);
	void Draw(void);
	void Update(void);
	void TakeDamage(int DamageCnt);
private:
	XFILE mesh;
	D3DXMATRIX mat;
	D3DXVECTOR3 pos;		//�O���[�o�����W�Ǘ�
	int HP = 5;		//���̒l
	int CoolTime = 3 * GameFPS;	//���̒l
};