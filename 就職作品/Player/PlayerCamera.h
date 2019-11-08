#pragma once
#include<d3dx9.h>
class PlayerCamera {
private:
	HWND hwnd;
	POINT basePt;
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	int SCRw, SCRh;
	const float camHight = 5.0f;
	D3DXMATRIX billBoardMat;		//作ったビルボードの行列を入れておく
public:
	PlayerCamera(int, int, HWND);
	~PlayerCamera();
	void SetCamera(void);
	void SetCamPos(D3DXVECTOR3*);
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetbillBoardMat(void);
};

extern LPDIRECT3DDEVICE9 lpD3DDevice;	// Direct3DDeviceインターフェイス