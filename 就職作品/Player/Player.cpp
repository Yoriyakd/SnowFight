#include "Player.h"
 
const float Player::camHight = 5.0f;
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
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerCam->GetCamAngY()));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerCam->GetCamAngY() + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerCam->GetCamAngY() - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerCam->GetCamAngY() + 90));
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
		snowBall_P.push_back(new SnowBall(pos, (playerCam->GetCamAngX() * -1), playerCam->GetCamAngY(), 1));
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
	
	

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mat);

	//--------------------------------------------------------------
	//カメラ回りの初期化
	//--------------------------------------------------------------
	
	playerCam = new PlayerCamera(SCRW, SCRH, hwnd);
	
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

	playerCam->SetCamPos(&D3DXVECTOR3 (pos.x, pos.y + camHight, pos.z));
	return true;
}

void Player::SetCamera(void)
{
	playerCam->SetCamera();
	
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
