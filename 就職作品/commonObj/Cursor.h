#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"

#define GetCursor Cursor::GetInstance()

class Cursor : public SingletonBase<Cursor>{
	friend class SingletonBase<Cursor>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	void Draw();
	void Update();
	void ShowCursor(bool State);
private:
	Cursor();
	~Cursor();

	bool isShow;

	LPDIRECT3DTEXTURE9 cursorTex;
	D3DXMATRIX cursorMat;
};

Cursor* SingletonBase<Cursor>::instance = nullptr;