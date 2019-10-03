#include "Player.h"
 
const float Player::camHight = 5.0f;
extern ResourceManager *resourceManager;
//=====================================
//private���\�b�h
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

	D3DXVec3Normalize(&movePos, &movePos);			//�ړ��ʐ��K��

	movePos *= moveSpeed;		//�ړ��X�s�[�h����

	if (moveFlag)
	{
		pos += movePos;
	}
}

int Player::ShootSnowball(SnowBallManager *snowBallManager)
{
	static bool KyeFlag = false;
	static float TimeCnt = 0;
	static const float MaxPowerTime = 3;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		KyeFlag = true;
		TimeCnt++;
	}
	else
	{
		if (KyeFlag == true)
		{
			float PowerPCT;
			if (TimeCnt > MaxPowerTime * FPS)TimeCnt = MaxPowerTime * FPS;
			PowerPCT = (float)TimeCnt / (float)(MaxPowerTime * FPS) * 100.0f;	//���������߂�

			SnowBallInitValue ValueTmp;
			ValueTmp.shootPos = pos;
			ValueTmp.XAxisAng = playerCam->GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
			ValueTmp.YAxisAng = playerCam->GetCamAngY();
			ValueTmp.powerRate = PowerPCT;
			ValueTmp.id = PLAYER_ID;
			
			snowBallManager->SetSnowBall(&ValueTmp);
			TimeCnt = 0;
			KyeFlag = false;
		}
	}
	return 0;		//�c�e����n��
}

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	moveSpeed = 0.5;		//test
	mesh = resourceManager->GetXFILE("Player/player.x");
	
	

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mat);

	//--------------------------------------------------------------
	//�J�������̏�����
	//--------------------------------------------------------------
	
	playerCam = new PlayerCamera(SCRW, SCRH, hwnd);
	
}

Player::~Player()
{
	
}

bool Player::Update(SnowBallManager *snowBallManager)
{
	Move();
	ShootSnowball(snowBallManager);
	

	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);		
	
	

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
}
