#pragma once
#include<d3dx9.h>
#include"../main.h"
//----------------------------------------
//プレイヤーのカメラクラス
//移動や視点操作を担当
//----------------------------------------
class PlayerCamera {
public:
	PlayerCamera();
	~PlayerCamera();
	void Update(StageBorder & StageBorder);
	void SetCamera(void);
	//--------------------------------------------------
	//Getter
	//--------------------------------------------------
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetmView(void);
	D3DXVECTOR3 GetmoveVec(void);					//プレイヤーの移動ベクトルを返す
	D3DXVECTOR3 GetPos(void);
	//--------------------------------------------------
	//Setter
	//--------------------------------------------------
	void PushPos(D3DXVECTOR3 *PushVec);				//押し出すベクトルを与える(当たり判定のところで使う)
	void SetPos(D3DXVECTOR3 *SetPos);
	void SetMakeSnowBaallFlag(bool Flag);			//

private:
	//--------------------------------------------------
	//マウスでカメラを動かす用の変数群
	//--------------------------------------------------
	POINT basePt;
	//--------------------------------------------------
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	//-------------------------------------------------
	//設定用の変数(ここの値を変更する)
	//-------------------------------------------------
	const float moveSpeed = 0.5f;
	const float camHight = 5.0f;		//カメラのy0からの高さ
	//-------------------------------------------------

	D3DXMATRIX billBoardMat;		//作ったビルボードの行列を入れておく
	D3DXVECTOR3 moveVec;		//移動ベクトルを保存しておき判定時に渡す
	D3DXMATRIX mView, mProj;		//視点行列,投影行列

	bool MakeSnowBallFlag;		//trueの時雪玉作成の姿勢になる
	float mouseSensitivityX = 1.0f, mouseSensitivityY = 1.0f;			//マウス感度調整用変数
	//--------------------------------------------------
	//メソッド
	//--------------------------------------------------
	void Move(StageBorder & StageBorder);
	void MakeSnowBallPose(void);

};
