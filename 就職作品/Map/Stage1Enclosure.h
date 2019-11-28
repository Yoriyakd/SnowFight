#pragma once
#include"../ResourceManager.h"
#include"../main.h"
class Stage1Enclosure {
public:
	Stage1Enclosure(StageBorder *StageBorder);
	~Stage1Enclosure();
	void Draw();
private:
	LPDIRECT3DTEXTURE9 hedgeTex, brickTex, poleTex;
	VERTEX vEnclosure[4];
	StageBorder *p_StageBorder;		//ステージ境界データのポインタを保存
};