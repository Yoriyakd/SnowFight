#include "PlayerCamera.h"
#include"../GameScene/GameScene.h"		//ステージサイズの情報共有のため

//=====================================
//publicメソッド
//=====================================

PlayerCamera::PlayerCamera()
{
	basePt.x = SCRW / 2;
	basePt.y = SCRH / 2;
	angX = 0, angY = 0;		//初期化
	ClientToScreen(hwnd, &basePt);		//元がクライアント座標なのでスクリーン座標に変換する(画面の中央に設定される)
	SetCursorPos(basePt.x, basePt.y);
	D3DXMatrixIdentity(&billBoardMat);
	moveSpeed = 0.5;		//移動速度
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(StageBorder & StageBorder)
{
	POINT Pt;
	ClientToScreen(hwnd, &Pt);		//スクリーン座標座標に変換
	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	angY += (Pt.x - basePt.x) / 4.0f;	//最初の位置との差を求め、移動量を調整している

	angX += (Pt.y - basePt.y) / 4.0f;
	SetCursorPos(basePt.x, basePt.y);	//カーソル位置リセット

	if (angX >= 70)
	{
		angX = 70;
	}

	if (angX <= -70)
	{
		angX = -70;
	}

	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(angY));				//傾いた分だけ回転させる

	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(angX));				//傾いた分だけ回転させる

	rotMat = rotMatX * rotMatY;

	Move(StageBorder);
}

void PlayerCamera::SetCamera(void)
{
	D3DXVECTOR3 camTmpVec, camHead;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &rotMat);	//最初の向きと傾いた分のベクトルを合わせる
	D3DXVec3TransformCoord(&camHead, &D3DXVECTOR3(0, 1, 0), &rotMat);	//最初の向きと傾いた分のベクトルを合わせる

	//視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y, pos.z),	// カメラの位置	
		&(D3DXVECTOR3(pos.x, pos.y, pos.z) + camTmpVec),	// カメラの視点
		&camHead	// カメラの頭の方向
	);


	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 2000.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}


float PlayerCamera::GetCamAngX(void)
{
	return angX;
}

float PlayerCamera::GetCamAngY(void)
{
	return angY;
}

D3DXMATRIX PlayerCamera::GetmView(void)
{
	return mView;
}

D3DXVECTOR3 PlayerCamera::GetmoveVec(void)
{
	return moveVec;
}

D3DXVECTOR3 PlayerCamera::GetPos(void)
{
	return pos;
}

void PlayerCamera::PushPos(D3DXVECTOR3 *PushVec)
{
	pos += *PushVec;
}

void PlayerCamera::SetPos(D3DXVECTOR3 * SetPos)
{
	pos = *SetPos;
	pos.y = camHight;
}

//=====================================
//privateメソッド
//=====================================
void PlayerCamera::Move(StageBorder & StageBorder)
{

	moveVec = D3DXVECTOR3(0, 0, 0);
	bool moveFlag = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY + 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}

	D3DXVec3Normalize(&moveVec, &moveVec);			//移動量正規化

	moveVec *= moveSpeed;		//移動スピード調整

	if (moveFlag == true)
	{
		pos += moveVec;
	}

	//ステージ境界の処理
	if (pos.z > StageBorder.Top)
	{
		pos.z += StageBorder.Top - pos.z;
	}

	if (pos.z < StageBorder.Bottom)
	{
		pos.z += StageBorder.Bottom - pos.z;
	}

	if (pos.x < StageBorder.Left)
	{
		pos.x += StageBorder.Left - pos.x;
	}

	if (pos.x > StageBorder.Right)
	{
		pos.x += StageBorder.Right - pos.x;
	}

}
