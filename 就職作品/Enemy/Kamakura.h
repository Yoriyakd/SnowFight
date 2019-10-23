#pragma once
#include"../main.h"
class Kamakura {
private:
	XFILE mesh;
	D3DXMATRIX mat;
	D3DXVECTOR3 pos;		//グローバル座標管理
	int HP = 5;		//仮の値
	int CoolTime = 3 * GameFPS;	//仮の値
	void SpawnEnemise(void);
public:
	Kamakura();
	~Kamakura();
	void SetPos(D3DXVECTOR3 Pos);
	void Draw(void);
	void Update(void);
	void DoDamage(int DamageCnt);
};