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

void Player::ShootSnowball(SnowBallManager *snowBallManager)
{
	static bool LKyeFlag = false;
	static float TimeCnt = 0;
	static const float MaxPowerTime = 3;		//最大溜めまでにかかる時間

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
				PowerPCT = (float)TimeCnt / (float)(MaxPowerTime * GameFPS) * 100.0f;	//割合を求める

				SnowBallInitValue ValueTmp;
				ValueTmp.shootPos = pos;
				ValueTmp.shootPos.y += 3;							//発射位置調整(変数化)
				ValueTmp.XAxisAng = playerCam->GetCamAngX() * -1;	//カメラのX軸角度をそのまま渡すと上向きが-なので反転させてる
				ValueTmp.YAxisAng = playerCam->GetCamAngY();
				ValueTmp.powerRate = PowerPCT;
				ValueTmp.id = PLAYER_ID;

				snowBallManager->SetSnowBall(&ValueTmp);
				TimeCnt = 0;
				LKyeFlag = false;
				remainingBalls--;		//発射したら残数を1減らす
			}
		}
	}
}

void Player::MakeBall()
{
	static bool RKyeFlag = false;
	static float MakeingTimeCnt = 0;
	static const float MakeTime = 3;		//作成に必要な時間
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
			MakeingTimeCnt = 0;		//リセット
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
		}
	}
}

//=====================================
//publicメソッド
//=====================================

Player::Player()
{
	int StartBallCnt = 5;	//スタート時のボールの数 プレイヤーの強化のデータを拾ってきて入れるようにする

	moveSpeed = 0.5;		//移動速度
	mesh = resourceManager->GetXFILE("Player/player.x");

	remainingBalls = StartBallCnt;
	ballMesh = resourceManager->GetXFILE("commonObj/SnowBall.x");



	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//スタートポイント
	D3DXMatrixIdentity(&mat);

	//--------------------------------------------------------------
	//カメラ回りの初期化
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

	playerCam->SetCamPos(&D3DXVECTOR3(pos.x, pos.y + camHight, pos.z));		//カメラの更新		※プレイヤーが移動した後に呼ぶ
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
	//作成中の雪玉表示
	//--------------------------------------------------------------

	D3DXMatrixTranslation(&ballMat, 0, 2, 3);		//プレイヤーとどれぐらい離れているか
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(playerCam->GetCamAngY()));
	ballMat = ballScalMat * ballMat * rotMat * mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);
}

int Player::GetRemainingBalls()
{
	return remainingBalls;
}