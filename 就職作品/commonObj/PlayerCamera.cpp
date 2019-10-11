#include "PlayerCamera.h"
//SCRW, SCRH, HWND
PlayerCamera::PlayerCamera(int Scrw, int Scrh, HWND Hwnd)
{
	hwnd = Hwnd;
	SCRw = Scrw;
	SCRh = Scrh;
	basePt.x = SCRw / 2;
	basePt.y = SCRh / 2;
	angX = 0, angY = 0;		//初期化
	ClientToScreen(hwnd, &basePt);
	SetCursorPos(basePt.x, basePt.y);
	ShowCursor(FALSE);			//カーソルを表示しない	※FALSEの回数をカウントしているので必要以上に呼ばない
}

PlayerCamera::~PlayerCamera()
{
	ShowCursor(TRUE);			//カーソルを表示する	※FTRUEの回数をカウントしているので必要以上に呼ばない
}

void PlayerCamera::SetCamera(void)
{
	D3DXMATRIX mView, mProj;

	
	POINT Pt;
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

	D3DXVECTOR3 camTmpVec;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &rotMat);	//最初の向きと傾いた分のベクトルを合わせる

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y, pos.z),	// カメラの位置	
		&(D3DXVECTOR3(pos.x, pos.y, pos.z) + camTmpVec),	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);
	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRw / (float)SCRh, 1.0f, 2000.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void PlayerCamera::SetCamPos(D3DXVECTOR3* pPos)
{
	pos = *pPos;
}

float PlayerCamera::GetCamAngX(void)
{
	return angX;
}

float PlayerCamera::GetCamAngY(void)
{
	return angY;
}
