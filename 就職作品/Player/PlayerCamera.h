#pragma once
#include<d3dx9.h>
#include"../main.h"
class PlayerCamera {
public:
	PlayerCamera(int, int, HWND);
	~PlayerCamera();
	void Update(void);
	void SetCamera(void);
	//--------------------------------------------------
	//Getter
	//--------------------------------------------------
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetbillBoardMat(void);
	D3DXVECTOR3 GetmoveVec(void);
	D3DXVECTOR3 GetPos(void);
	//--------------------------------------------------
	//Setter
	//--------------------------------------------------
	void PushPos(D3DXVECTOR3 *PushVec);

private:
	//--------------------------------------------------
	//マウスでカメラを動かす用の変数群
	//--------------------------------------------------
	HWND hwnd;
	POINT basePt;
	int SCRw, SCRh;		//スクリーンのサイズ保存用
	//--------------------------------------------------
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	float moveSpeed;
	
	const float camHight = 5.0f;		//カメラのy0からの高さ


	D3DXMATRIX billBoardMat;		//作ったビルボードの行列を入れておく
	D3DXVECTOR3 moveVec;		//移動ベクトルを保存しておき判定時に渡す
	//--------------------------------------------------
	//メソッド
	//--------------------------------------------------
	void Move(void);

};

extern LPDIRECT3DDEVICE9 lpD3DDevice;	// Direct3DDeviceインターフェイス