#include "Player.h"
#include"../Map/LoadStageData.h"
#include"../GameScene/GameScene.h"

extern ResourceManager *resourceManager;
const float Player::MaxPowerTime = 1.5f;

//=====================================
//privateメソッド
//=====================================

void Player::Move(void)
{
	moveVec = D3DXVECTOR3(0, 0, 0);
	bool moveFlag = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY()));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY() + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY() - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(pPlayerCam->GetCamAngY() + 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}

	D3DXVec3Normalize(&moveVec, &moveVec);			//移動量正規化

	moveVec *= moveSpeed;		//移動スピード調整

	if (moveFlag)
	{
		pos += moveVec;
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

	if (remainingBalls > 0) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			LKyeFlag = true;
			timeCnt++;

			if (timeCnt > MaxPowerTime * GameFPS)
			{
				shootPowerPCT = 80;		//最大溜めの速さ
			}
			else
			{
				shootPowerPCT = 30 + 50 * (timeCnt / (MaxPowerTime * GameFPS));		//30や50は何となくで決めている
			}


			//--------------------------------------------------
			//雪玉軌跡表示処理
			//--------------------------------------------------
			
			MakeGhostMat(&MakeSnowBallInitValue());

			////--------------------------------------------------
			////腕回転処理
			////--------------------------------------------------
			//static const float MaxAng = 120;
			//armAng = MaxAng * (timeCnt / (MaxPowerTime * GameFPS));

			//D3DXMatrixRotationX(&armRotMatXR, D3DXToRadian(-armAng));

		}
		else
		{
			ghostMat.clear();	//押してないときは非表示
			if (LKyeFlag == true)
			{
				MakeSnowBallInitValue();
				snowBallManager->SetSnowBall(&MakeSnowBallInitValue());
				timeCnt = 0;
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

	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;


	moveVec = SnowBallInit(snowBallInitValue, &TmpMat);

	D3DXMatrixTranslation(&TmpMat, snowBallInitValue->shootPos.x, snowBallInitValue->shootPos.y, snowBallInitValue->shootPos.z);			//発射位置

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(snowBallInitValue->YAxisAng));		//発射元の角度から行列作成
	TmpMat = TmpRot * TmpMat;

	ghostMat.push_back(TmpMat);
	//----------------------------------
	//while文で地面衝突まで回す
	//----------------------------------
	while (1)
	{
		D3DXMATRIX MoveMat;			//移動が終わった後の行列
		moveVec.y += Gravity;

		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
		TmpMat = MoveMat * TmpMat;
		ghostMat.push_back(TmpMat);
		if (TmpMat._42 < 0)break;
	}
}

SnowBallInitValue Player::MakeSnowBallInitValue()
{
	D3DXVECTOR3 ShootOffset;	//回転を考慮した座標を入れる
	SnowBallInitValue _SnowBallInitValue;

	D3DXVec3TransformCoord(&ShootOffset, &shootOffset, &rotMat);	//回転を考慮したベクトル作成

	_SnowBallInitValue.shootPos = pos + ShootOffset;
	_SnowBallInitValue.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//カメラのX軸角度をそのまま渡すと上向きが-なので反転させてる
	_SnowBallInitValue.YAxisAng = pPlayerCam->GetCamAngY();
	_SnowBallInitValue.powerRate = shootPowerPCT;
	_SnowBallInitValue.id = PLAYER_ID;
	return _SnowBallInitValue;
}

//=====================================
//publicメソッド
//=====================================

Player::Player()
{
	//--------------------------------------------------------------
	//プレイヤー初期化
	//--------------------------------------------------------------
	int StartBallCnt = 10;	//スタート時のボールの数 プレイヤーの強化のデータを拾ってきて入れるようにする

	moveSpeed = 0.5;		//移動速度
	mesh = resourceManager->GetXFILE("player.x");

	remainingBalls = StartBallCnt;
	
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//スタートポイント
	D3DXMatrixIdentity(&mat);

	GhostTex = resourceManager->GetTexture("Locus.png", 64, 64, NULL);

	//--------------------------------------------------------------
	//腕
	//--------------------------------------------------------------
	//armMeshR = resourceManager->GetXFILE("ArmR.x");
	//D3DXMatrixTranslation(&armOffsetMatR, 1.0f, -2.0f, 0.0f);		//プレイヤーの原点からの距離
	
	/*armAng = 0.0f;
	D3DXMatrixRotationX(&armRotMatXR, D3DXToRadian(-armAng));*/

	//--------------------------------------------------------------
	//雪玉
	//--------------------------------------------------------------
	ballMesh = resourceManager->GetXFILE("SnowBall.x");
	D3DXMatrixTranslation(&ballOffsetMat, 0, 2, 3);		//プレイヤーとどれぐらい離れているか
}

Player::~Player()
{

}

bool Player::Update(SnowBallManager *snowBallManager)
{
	Move();
	ShootSnowball(snowBallManager);
	MakeBall();

	//-------------------------------------------------------
	//プレイヤーの行列作成
	//-------------------------------------------------------
	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(pPlayerCam->GetCamAngY()));
	mat = rotMat * transMat;		//Y軸のみ

	//-------------------------------------------------------
	//腕の行列作成
	//-------------------------------------------------------
	/*D3DXMATRIX ParentMat, ParentRotX, ParentRotY, pRot, camTrans;
	camTrans = transMat;
	camTrans._42 += 5;
	
	D3DXMatrixRotationX(&ParentRotX, D3DXToRadian(pPlayerCam->GetCamAngX()));
	D3DXMatrixRotationY(&ParentRotY, D3DXToRadian(pPlayerCam->GetCamAngY()));

	D3DXVECTOR3 armOffsetVec(1.0f, -2.0f, 0.0f);
	pRot = ParentRotX * ParentRotY;
	D3DXVec3TransformNormal(&armOffsetVec, &armOffsetVec, &pRot);
	D3DXMatrixTranslation(&armOffsetMatR, armOffsetVec.x, armOffsetVec.y, armOffsetVec.z);

	armMatR = armOffsetMatR * pRot * camTrans;*/
	 



	if (GetAsyncKeyState('O') & 0x8000)		//デバッグ ☆
	{
		remainingBalls += 10;
	}
	
	return true;
}

void Player::SetCamera(void)
{
	

}

void Player::Draw(void)
{
	//--------------------------------------------------------------
	//プレイヤー表示
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//腕表示
	//--------------------------------------------------------------
	/*lpD3DDevice->SetTransform(D3DTS_WORLD, &armMatR);
	DrawMesh(&armMeshR);*/

	//--------------------------------------------------------------
	//作成中の雪玉表示
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング

	ballMat = ballScalMat * ballOffsetMat * mat;
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

D3DXVECTOR3 Player::GetMoveVec(void)
{
	return moveVec;
}

void Player::PushPlayer(D3DXVECTOR3 * PushVec)
{
	pos += *PushVec;
}
