#include "Player.h"

extern ResourceManager *resourceManager;
//=====================================
//privateメソッド
//=====================================

void Player::Move(void)
{
	D3DXVECTOR3 movePos(0, 0, 0);
	 bool moveFlag = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY + 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}

	D3DXVec3Normalize(&movePos, &movePos);			//移動量正規化

	movePos *= moveSpeed;		//移動スピード調整

	if (moveFlag)
	{
		pos += movePos;
	}
}

int Player::ShootSnowball(void)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		snowBall_P.push_back(new SnowBall(pos, camAngY));
	}
	return 0;		//残弾数を渡す
}

//=====================================
//publicメソッド
//=====================================

Player::Player()
{
	moveSpeed = 0.5;		//test
	mesh = resourceManager->GetXFILE("Player/player.x");
	
	camAngX = 0, camAngY = 0;		//初期化

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mat);

	//--------------------------------------------------------------
	//カメラ回りの初期化
	//--------------------------------------------------------------
	basePt.x = SCRW / 2;
	basePt.y = SCRH / 2;

	ClientToScreen(hwnd, &basePt);
	SetCursorPos(basePt.x, basePt.y);

	
}

Player::~Player()
{
	for (unsigned int i = 0; i < snowBall_P.size(); i++)
	{
		delete snowBall_P[i];
	}
	snowBall_P.clear();
}

bool Player::Update(void)
{
	Move();
	ShootSnowball();
	//D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);		//仮
	//D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);		//仮
	//mat = transMat * mat;		//合成すると(0, 0, 10)のやつを合成し続けるような形になる	変化があった時のみ合成とかでもいけるかも
	

	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);		
	
	for (unsigned int i = 0; i < snowBall_P.size(); i++)
	{
		if (snowBall_P[i]->Update() == false)
		{
			delete snowBall_P[i];
			snowBall_P.erase(snowBall_P.begin() + i);
			i--;
		}
	}

	return true;
}

void Player::SetCamera(void)
{
	D3DXMATRIX mView, mProj;

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		AngY++;
	}*/

	

	POINT Pt;					
	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	camAngY += (Pt.x - basePt.x) / 4.0f;	//最初の位置との差を求め、移動量を調整している
	
	camAngX += (Pt.y - basePt.y) / 4.0f;
	SetCursorPos(basePt.x, basePt.y);	//カーソル位置リセット

	if (camAngX >= 70)
	{
		camAngX = 70;
	}
	
	if (camAngX <= -70)
	{
		camAngX = -70;
	}

	D3DXMatrixRotationY(&camRotMatY, D3DXToRadian(camAngY));				//傾いた分だけ回転させる
	
	D3DXMatrixRotationX(&camRotMatX, D3DXToRadian(camAngX));				//傾いた分だけ回転させる

	camRotMat = camRotMatX * camRotMatY;

	D3DXVECTOR3 camTmpVec;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &camRotMat);	//最初の向きと傾いた分のベクトルを合わせる

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y + 5, pos.z ),	// カメラの位置						//カメラの変数を用意した方がいい
		&(D3DXVECTOR3(pos.x, pos.y + 5, pos.z) + camTmpVec),	// カメラの視点		//カメラの変数を用意した方がいい	
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);
	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void Player::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
	for (unsigned int i = 0; i < snowBall_P.size(); i++)
	{
		snowBall_P[i]->Draw();
	}
}
