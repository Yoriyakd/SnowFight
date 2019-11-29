#pragma once
#include<d3dx9.h>
#include"../main.h"
class PlayerCamera {
public:
	PlayerCamera();
	~PlayerCamera();
	void Update(void);
	void SetCamera(void);
	//--------------------------------------------------
	//Getter
	//--------------------------------------------------
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetmView(void);
	D3DXVECTOR3 GetmoveVec(void);
	D3DXVECTOR3 GetPos(void);
	//--------------------------------------------------
	//Setter
	//--------------------------------------------------
	void PushPos(D3DXVECTOR3 *PushVec);
	void SetPos(D3DXVECTOR3 *SetPos);

private:
	//--------------------------------------------------
	//マウスでカメラを動かす用の変数群
	//--------------------------------------------------
	POINT basePt;
	//--------------------------------------------------
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	float moveSpeed;
	
	const float camHight = 5.0f;		//カメラのy0からの高さ


	D3DXMATRIX billBoardMat;		//作ったビルボードの行列を入れておく
	D3DXVECTOR3 moveVec;		//移動ベクトルを保存しておき判定時に渡す
	D3DXMATRIX mView, mProj;		//視点行列,投影行列
	//--------------------------------------------------
	//メソッド
	//--------------------------------------------------
	void Move(void);

};

extern LPDIRECT3DDEVICE9 lpD3DDevice;	// Direct3DDeviceインターフェイス