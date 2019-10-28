#include "Player.h"
#include"../Map/LoadStageData.h"
//#include"../GameScene/GameScene.h"

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
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY()));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY() + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY() - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY() + 90));
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

	//ステージ境界の処理
	if (pos.z > stageBorder.Top)
	{
		pos.z += stageBorder.Top - pos.z;
	}

	if (pos.z < stageBorder.Bottom)
	{
		pos.z += stageBorder.Bottom - pos.z;
	}

	if (pos.x < stageBorder.Left)
	{
		pos.x += stageBorder.Left - pos.x;
	}

	if (pos.x > stageBorder.Right)
	{
		pos.x += stageBorder.Right - pos.x;
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
			//--------------------------------------------------
			//雪玉軌跡表示処理
			//--------------------------------------------------
			float PowerPCT;
			if (TimeCnt > MaxPowerTime * GameFPS)
			{
				PowerPCT = 100;		//最大溜めの速さ
			}
			else
			{
				PowerPCT = 30;		//最大溜めいがいの速さ
			}
			
			SnowBallInitValue GhostTmp;
			GhostTmp.shootPos = pos;
			GhostTmp.shootPos.y += 3;							//発射位置調整(変数化)
			GhostTmp.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//カメラのX軸角度をそのまま渡すと上向きが-なので反転させてる
			GhostTmp.YAxisAng = pPlayerCam->GetCamAngY();
			GhostTmp.powerRate = PowerPCT;
			GhostTmp.id = PLAYER_ID;

			MakeGhostMat(&GhostTmp);

		}
		else
		{
			ghostMat.clear();	//押してないときは非表示
			if (LKyeFlag == true)
			{
				float PowerPCT;
				if (TimeCnt > MaxPowerTime * GameFPS)
				{
					PowerPCT = 100;		//最大溜めの速さ
				}
				else
				{
					PowerPCT = 30;		//最大溜めいがいの速さ
				}
				

				SnowBallInitValue ValueTmp;
				ValueTmp.shootPos = pos;
				ValueTmp.shootPos.y += 3;							//発射位置調整(変数化)
				ValueTmp.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//カメラのX軸角度をそのまま渡すと上向きが-なので反転させてる
				ValueTmp.YAxisAng = pPlayerCam->GetCamAngY();
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
			if (MakeingTimeCnt >= MakeTime * GameFPS)		//作っていた時間が作るのに必要な時間以上なら作成完了
			{
				remainingBalls++;
			}
			else
			{
				//足りなければ壊れる
				//SnowFragエフェクト呼ぶ
				effectManager->snowFrag.push_back(new SnowFrag((D3DXVECTOR3(ballMat._41, ballMat._42, ballMat._43))));
			}
			RKyeFlag = false;
			MakeingTimeCnt = 0;		//リセット
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
		}
	}
}

void Player::MakeGhostMat(SnowBallInitValue *snowBallInitValue)
{
	ghostMat.clear();	//初期化
	float Power;
	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;
	Power = ((snowBallInitValue->powerRate / 100)) * 5;

	D3DXMatrixTranslation(&TmpMat, snowBallInitValue->shootPos.x, snowBallInitValue->shootPos.y, snowBallInitValue->shootPos.z);			//発射位置

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(snowBallInitValue->XAxisAng))), (Power * cos(D3DXToRadian(snowBallInitValue->XAxisAng))));

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(snowBallInitValue->YAxisAng));
	TmpMat = TmpRot * TmpMat;

	ghostMat.push_back(TmpMat);
	//----------------------------------
	//while文で地面衝突まで回す
	//----------------------------------
	while (1)
	{
		D3DXMATRIX MoveMat;			//移動が終わった後の行列
		moveVec.y += -0.02f;

		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
		TmpMat = MoveMat * TmpMat;
		ghostMat.push_back(TmpMat);
		if (TmpMat._42 < 0)break;
	}
}

//=====================================
//publicメソッド
//=====================================

Player::Player()
{
	int StartBallCnt = 10;	//スタート時のボールの数 プレイヤーの強化のデータを拾ってきて入れるようにする

	moveSpeed = 0.5;		//移動速度
	mesh = resourceManager->GetXFILE("Player/player.x");

	remainingBalls = StartBallCnt;
	ballMesh = resourceManager->GetXFILE("commonObj/SnowBall.x");



	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//スタートポイント
	D3DXMatrixIdentity(&mat);

	GhostTex = resourceManager->GetTexture("Player/Locus.png", 64, 64, NULL);
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

	
	return true;
}

void Player::SetCamera(void)
{
	

}

void Player::Draw(void)
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//作成中の雪玉表示
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	D3DXMatrixTranslation(&ballMat, 0, 2, 3);		//プレイヤーとどれぐらい離れているか
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(pPlayerCam->GetCamAngY()));
	ballMat = ballScalMat * ballMat * rotMat * mat;
	lpD3DDevice->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);

	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//--------------------------------------------------------------
	//軌道の表示
	//--------------------------------------------------------------
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//加算合成オン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Zバッファ書き込みオフ

	VERTEX vertex[4];

	vertex[0].Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(128, 255, 255, 255);

	for (unsigned int i = 0; i < (ghostMat.size() - 1); i++)
	{
		if (ghostMat.size() == 0)
		{
			break;
		}
		vertex[0].Tex = D3DXVECTOR2(0.0f, (float)i / (ghostMat.size() - 1));
		vertex[1].Tex = D3DXVECTOR2(1.0f, (float)i / (ghostMat.size() - 1));
		vertex[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (ghostMat.size() - 1));
		vertex[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (ghostMat.size() - 1));


		D3DXVec3TransformCoord(&vertex[0].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f),&ghostMat[i]);		//ポインタ型で宣言していたらPosぼ値がnanになっていた
		D3DXVec3TransformCoord(&vertex[1].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &ghostMat[i]);
		D3DXVec3TransformCoord(&vertex[2].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &ghostMat[i + 1]);
		D3DXVec3TransformCoord(&vertex[3].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &ghostMat[i + 1]);

		lpD3DDevice->SetTexture(0, GhostTex);
		D3DXMATRIX IdenMat;
		D3DXMatrixIdentity(&IdenMat);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));
	}



	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン

}

int Player::GetRemainingBalls()
{
	return remainingBalls;
}

void Player::SetStageBorder(StageBorder StageBorder)
{
	stageBorder = StageBorder;
}

D3DXVECTOR3 Player::GetPlayerPos(void)
{
	return pos;
}

void Player::SetPlayerCamPointer(PlayerCamera * PPlayerCam)
{
	pPlayerCam = PPlayerCam;
}
