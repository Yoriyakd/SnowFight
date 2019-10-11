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

void Player::ShootSnowball(SnowBallManager *snowBallManager)
{
	static bool LKyeFlag = false;
	static float TimeCnt = 0;
	static const float MaxPowerTime = 3;		//�ő嗭�߂܂łɂ����鎞��

	if (remainingBalls > 0) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			LKyeFlag = true;
			TimeCnt++;
		}
		else
		{
			if (LKyeFlag == true)
			{
				float PowerPCT;
				if (TimeCnt > MaxPowerTime * GameFPS)TimeCnt = MaxPowerTime * GameFPS;
				PowerPCT = (float)TimeCnt / (float)(MaxPowerTime * GameFPS) * 100.0f;	//���������߂�

				SnowBallInitValue ValueTmp;
				ValueTmp.shootPos = pos;
				ValueTmp.shootPos.y += 3;							//���ˈʒu����(�ϐ���)
				ValueTmp.XAxisAng = playerCam->GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
				ValueTmp.YAxisAng = playerCam->GetCamAngY();
				ValueTmp.powerRate = PowerPCT;
				ValueTmp.id = PLAYER_ID;

				snowBallManager->SetSnowBall(&ValueTmp);
				TimeCnt = 0;
				LKyeFlag = false;
				remainingBalls--;		//���˂�����c����1���炷
			}
		}
	}
}

void Player::MakeBall()
{
	static bool RKyeFlag = false;
	static float MakeingTimeCnt = 0;
	static const float MakeTime = 3;		//�쐬�ɕK�v�Ȏ���
	static float ballSize = 0;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		RKyeFlag = true;
		MakeingTimeCnt++;
		if (MakeingTimeCnt > MakeTime * GameFPS)
		{
			MakeingTimeCnt = MakeTime * GameFPS;
		}

		const float MaxBallScal = 1.5;
		ballSize = MakeingTimeCnt / (MakeTime * GameFPS) * MaxBallScal;

		D3DXMatrixScaling(&ballScalMat, ballSize, ballSize, ballSize);
	}
	else
	{
		if (RKyeFlag == true)
		{
			if (MakeingTimeCnt >= MakeTime * GameFPS)
			{
				remainingBalls++;
			}
			RKyeFlag = false;
			MakeingTimeCnt = 0;		//���Z�b�g
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
		}
	}
}

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	int StartBallCnt = 5;	//�X�^�[�g���̃{�[���̐� �v���C���[�̋����̃f�[�^���E���Ă��ē����悤�ɂ���

	moveSpeed = 0.5;		//�ړ����x
	mesh = resourceManager->GetXFILE("Player/player.x");

	remainingBalls = StartBallCnt;
	ballMesh = resourceManager->GetXFILE("commonObj/SnowBall.x");



	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�X�^�[�g�|�C���g
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
	MakeBall();

	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

	playerCam->SetCamPos(&D3DXVECTOR3(pos.x, pos.y + camHight, pos.z));		//�J�����̍X�V		���v���C���[���ړ�������ɌĂ�
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

	//--------------------------------------------------------------
	//�쐬���̐�ʕ\��
	//--------------------------------------------------------------

	D3DXMatrixTranslation(&ballMat, 0, 2, 3);		//�v���C���[�Ƃǂꂮ�炢����Ă��邩
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(playerCam->GetCamAngY()));
	ballMat = ballScalMat * ballMat * rotMat * mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);
}

int Player::GetRemainingBalls()
{
	return remainingBalls;
}