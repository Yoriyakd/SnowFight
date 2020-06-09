#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"

#define GetCursor Cursor::GetInstance()

class Cursor : public SingletonBase<Cursor>{
	friend class SingletonBase<Cursor>;			//SingletonBaseでのインスタンス作成削除は許可
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
	const RECT RcCursor = { 0, 0, 64, 64 };
};