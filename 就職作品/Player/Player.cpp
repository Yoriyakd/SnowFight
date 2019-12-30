#include "Player.h"
#include"../GameScene/GameScene.h"

extern ResourceManager *resourceManager;


//=====================================
//publicメソッド
//=====================================

Player::Player()
{
	//--------------------------------------------------------------
	//プレイヤー初期化
	//--------------------------------------------------------------


	remainingBalls = StartBallCnt;

	GhostTex = GetResource.GetTexture(ThrowGhost_Tex);
	carryFlag = false;

	//--------------------------------------------------------------
	//靴
	//--------------------------------------------------------------
	shoesMesh = GetResource.GetXFILE(Shoes_M);
	D3DXMatrixTranslation(&shoesOffsetMat, 0, -5, 0);			//プレイヤーといくら離すか
	D3DXMatrixRotationX(&shoesRotMatX, D3DXToRadian(0));

	//--------------------------------------------------------------
	//腕
	//--------------------------------------------------------------
	armLMesh = GetResource.GetXFILE(ArmL_M);
	armRMesh = GetResource.GetXFILE(ArmR_M);

	D3DXMATRIX TmpRotZ, TmpRotX, TmpTransMat;

	D3DXMatrixTranslation(&TmpTransMat, -1.8f, -1.5f, -2.0f);
	D3DXMatrixRotationZ(&TmpRotZ, D3DXToRadian(-90));
	D3DXMatrixRotationX(&TmpRotX, D3DXToRadian(90));
	armLOffsetMat = TmpRotZ * TmpRotX * TmpTransMat;


	D3DXMatrixTranslation(&TmpTransMat, 1.8f, -1.5f, 3.0f);		//プレイヤーの原点からの距離
	D3DXMatrixRotationZ(&TmpRotZ, D3DXToRadian(30));
	armROffsetMat = TmpRotZ * TmpTransMat;

	
	
	
	//--------------------------------------------------------------
	//雪玉
	//--------------------------------------------------------------
	ballMesh = GetResource.GetXFILE(SnowBall_M);
	D3DXMatrixTranslation(&ballOffsetMat, 0.0f, -3.0f, 1.5f);		//プレイヤーといくら離すか
}

Player::~Player()
{
	delete ArmAnime;
}

bool Player::Update(SnowBallManager & SnowBallManager, DecorationManager & DecorationManager, PickUpInstructions & PickUpInstructions)
{
	//D3DXVECTOR3 NewPos;	☆
	//NewPos = pPlayerCam->GetPos();		//カメラの座標をセット
	//pos = NewPos;		//座標更新		動いているかの判定のため分けていた

	pos = pPlayerCam->GetPos();		//カメラの座標をセット

	//-----------------------------------------------------
	//デコレーション周り
	//-----------------------------------------------------
	if (DecorationManager.CheckForCanPicUp(&pos) == true)			//拾えるかのチェックだけ		
	{//運んでいるときは持ち運べない予定なので、はこんでいるときの指示は別に出す方がよさそう
		PickUpInstructions.TurnOnDisplay();		//拾える時画面に指示を表示
		if (carryFlag == false)		//今運んでいないなら
		{
			if (GetAsyncKeyState('F') & 0x8000)
			{
				carryDecorationID = DecorationManager.PickUp(&pos);				//拾う	近くに2つ以上アイテムがあると配列番号が若いものが優先して拾われてしまう
				carryFlag = true;
			}
		}
	}
	else
	{
		PickUpInstructions.TurnOffDisplay();
	}


	//-----------------------------------------------------



	//pos = D3DXVECTOR3(100, 5, 30);		//デバック用☆

	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(pPlayerCam->GetCamAngY()));		//カメラの回転から行列作成
	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(pPlayerCam->GetCamAngX()));		//カメラの回転から行列作成


	Throw(SnowBallManager, DecorationManager);
	MakeBall();

	//-------------------------------------------------------
	//靴の行列作成
	//-------------------------------------------------------
	shoesMat = shoesOffsetMat * shoesRotMatX * rotMatY * transMat;		//プレイヤーのX軸は回転しない

	//-------------------------------------------------------
	//腕の行列作成
	//-------------------------------------------------------
	if (ArmAnime != nullptr)
	{
		ArmAnimeBase *NextAnime;
		NextAnime = ArmAnime->Anime(&armLOffsetMat, &armROffsetMat);
		if (NextAnime != nullptr)
		{
			delete ArmAnime;
			ArmAnime = NextAnime;
		}
	}
	
	armRMat = armROffsetMat * rotMatX * rotMatY * transMat;		//カメラからの距離の距離の行列にカメラの行列から作った行列を合成してプレイヤーについていかせる
	armLMat = armLOffsetMat * rotMatX * rotMatY * transMat;
	 
	//-------------------------------------------------------
	//作成中の雪玉行列作成
	//-------------------------------------------------------
	ballMat = ballScalMat * ballOffsetMat * rotMatY * transMat;

	if (GetAsyncKeyState('O') & 0x8000)		//デバッグ ☆
	{
		remainingBalls += 10;
	}

	if (remainingBalls > 999)
	{
		remainingBalls = 999;			//カンストチェック
	}
	
	return true;
}

void Player::SetCamera(void)
{
	

}

void Player::Draw(void)
{
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
		if (ghostMat.size() == 0)		//軌跡が作られていない時は描画しない
		{
			break;
		}
		vertex[0].Tex = D3DXVECTOR2(0.0f, (float)i / (ghostMat.size() - 1));
		vertex[1].Tex = D3DXVECTOR2(1.0f, (float)i / (ghostMat.size() - 1));
		vertex[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (ghostMat.size() - 1));
		vertex[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (ghostMat.size() - 1));


		D3DXVec3TransformCoord(&vertex[0].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f),&ghostMat[i]);
		D3DXVec3TransformCoord(&vertex[1].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &ghostMat[i]);
		D3DXVec3TransformCoord(&vertex[2].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &ghostMat[i + 1]);
		D3DXVec3TransformCoord(&vertex[3].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &ghostMat[i + 1]);

		lpD3DDevice->SetTexture(0, GhostTex);
		D3DXMATRIX IdenMat;
		D3DXMatrixIdentity(&IdenMat);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));
	}


	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン
	   
	//--------------------------------------------------------------
	//作成中の雪玉表示
	//--------------------------------------------------------------
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 125), 1.0f, 0);		//Zバッファクリア	※GameSceneで最後に呼ぶ

	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング

	lpD3DDevice->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);

	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//--------------------------------------------------------------
	//靴表示
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &shoesMat);
	DrawMesh(&shoesMesh);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//腕表示
	//--------------------------------------------------------------
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 125), 1.0f, 0);		//Zバッファクリア	※GameSceneで最後に呼ぶ

	lpD3DDevice->SetTransform(D3DTS_WORLD, &armRMat);
	DrawMesh(&armRMesh);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &armLMat);
	DrawMesh(&armLMesh);
}

int Player::GetRemainingBalls()
{
	return remainingBalls;
}


D3DXVECTOR3 Player::GetPlayerPos(void)
{
	return pos;
}

void Player::GetCollisionSphere(CollisionSphere * CollisionSphere)
{
	CollisionSphere->pos = pos;
	CollisionSphere->radius = CollisionRadius;

}


void Player::SetPlayerCamPointer(PlayerCamera * PPlayerCam)
{
	pPlayerCam = PPlayerCam;
}

void Player::HitSnowBall()
{
	HP--;
}

int Player::GetHP()
{
	return HP;
}

//=====================================
//privateメソッド
//=====================================

void Player::Throw(SnowBallManager &SnowBallManager, DecorationManager & DecorationManager)
{
	static bool LKyeFlag = false;
	static bool AnimeFlag_T = false;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)		//雪玉を作っているとき
	{
		//発射をキャンセルする
		std::vector<D3DXMATRIX>().swap(ghostMat);		//メモリ開放
		AnimeFlag_T = false;
		timeCnt = 0;
		LKyeFlag = false;
		pPlayerCam->SetMoveSpeed(0.5);			//移動速度リセット	//定数化☆
		return;
	}

	if (remainingBalls > 0 || carryFlag == true) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			LKyeFlag = true;
			timeCnt++;

			pPlayerCam->SetMoveSpeed(0.3f);		//移動速度を遅くする

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
			MakeGhostMat(&MakeThrowValue());
		
			//腕アニメーション
			if (AnimeFlag_T == false)
			{
				AnimeFlag_T = true;
				delete ArmAnime;
				ArmAnime = new WindUpAnime(&armROffsetMat);
			}
		}
		else
		{
			std::vector<D3DXMATRIX>().swap(ghostMat);		//メモリ開放
			if (LKyeFlag == true)
			{
				if (carryFlag == true)			//デコレーションを運んでいる状態ではデコレーションを投げる
				{
					carryFlag = false;

					D3DXVECTOR3 DropPoinOffset;

					DropPoinOffset = D3DXVECTOR3(0, 2.0f, 5.0f);		//プレイヤーの少し前に落とすようにする
					D3DXVec3TransformCoord(&DropPoinOffset, &DropPoinOffset, &rotMatY);	//回転を考慮したベクトル作成

					DecorationManager.Throw(&(pos + DropPoinOffset), carryDecorationID, &MakeThrowValue());

					timeCnt = 0;
					LKyeFlag = false;
				}
				else
				{
					SnowBallManager.SetSnowBall(&MakeThrowValue(), PLAYER_ID);
					timeCnt = 0;
					LKyeFlag = false;
					remainingBalls--;		//発射したら残数を1減らす
				}
				pPlayerCam->SetMoveSpeed(0.5f);		//移動速度リセット	//定数化☆
				//腕アニメーション
				AnimeFlag_T = false;
				delete ArmAnime;
				ArmAnime = new ThrowAnime();
			}
		}
	}
}

void Player::MakeBall()
{
	static bool RKyeFlag = false;
	static float MakeingTimeCnt = 0;
	static float ballSize = 0;
	static bool AnimeFlag_MKB = false;

	

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		pPlayerCam->SetMakeSnowBallFlag(true);

		if (pPlayerCam->GetHasPosed() == true)
		{
			RKyeFlag = true;

			MakeingTimeCnt++;
			//--------------------------------------------
			//カメラと靴のアニメーションを開始する
			//--------------------------------------------

			ShoesMakeBallAnime(true);

			if (AnimeFlag_MKB == false)
			{
				delete ArmAnime;
				ArmAnime = new MakeSnowBallAnime(&armLOffsetMat, &armROffsetMat);
				AnimeFlag_MKB = true;
			}

			//--------------------------------------------
			
			ballSize = MakeingTimeCnt / (MakeTime * GameFPS) * MaxBallScal;			//時間経過で大きくなる

			D3DXMatrixScaling(&ballScalMat, ballSize, ballSize, ballSize);

			if (MakeingTimeCnt >= MakeTime * GameFPS)		//作っていた時間が作るのに必要な時間以上なら作成完了
			{
				remainingBalls++;
				MakeingTimeCnt = 0;		//リセット
				D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
			}
		}
	}
	else
	{
		pPlayerCam->SetMakeSnowBallFlag(false);
		ShoesMakeBallAnime(false);
		if (RKyeFlag == true)
		{
			//SnowFragエフェクト呼ぶ
			effectManager->NewSnowFrag((D3DXVECTOR3(ballMat._41, ballMat._42, ballMat._43)));

			RKyeFlag = false;
			MakeingTimeCnt = 0;		//リセット
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);

			//--------------------------------------------
			//カメラと靴のアニメーションを終了する
			//--------------------------------------------
			pPlayerCam->SetMakeSnowBallFlag(false);

			AnimeFlag_MKB = false;
			delete ArmAnime;
			ArmAnime = new ArmAnimeIdle(&armLOffsetMat, &armROffsetMat);
		}
	}

}

void Player::ShoesMakeBallAnime(bool AnimeState)
{
	if (AnimeState == true)
	{
		if (shoesAngX <= 90.0f)
		{
			shoesAngX += 10.0f;
		}
	}
	else
	{
		if (shoesAngX >= 0.0f)
		{
			shoesAngX -= 10.0f;
		}
	}

	D3DXMatrixRotationX(&shoesRotMatX, D3DXToRadian(shoesAngX));
}

void Player::MakeGhostMat(ThrowingInitValue *ThrowingInitValue)
{
	std::vector<D3DXMATRIX>().swap(ghostMat);		//メモリ開放

	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;


	moveVec = ThrowingInit(ThrowingInitValue, &TmpMat);

	D3DXMatrixTranslation(&TmpMat, ThrowingInitValue->shootPos.x, ThrowingInitValue->shootPos.y, ThrowingInitValue->shootPos.z);			//発射位置

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//発射元の角度から行列作成
	TmpMat = TmpRot * TmpMat;

	ghostMat.push_back(TmpMat);
	//----------------------------------
	//while文で地面衝突まで回す
	//----------------------------------
	while (1)
	{
		D3DXMATRIX MoveMat;			//移動が終わった後の行列
		moveVec.y += SnowBallGravity;

		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
		TmpMat = MoveMat * TmpMat;
		ghostMat.push_back(TmpMat);
		if (TmpMat._42 < 0)break;
	}
}

ThrowingInitValue Player::MakeThrowValue()
{
	D3DXVECTOR3 ShootOffset;	//回転を考慮した座標を入れる
	ThrowingInitValue _ThrowingBallInitValue;

	D3DXVec3TransformCoord(&ShootOffset, &shootOffset, &rotMatY);	//回転を考慮したベクトル作成

	_ThrowingBallInitValue.shootPos = pos + ShootOffset;
	_ThrowingBallInitValue.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//カメラのX軸角度をそのまま渡すと上向きが-なので反転させてる
	_ThrowingBallInitValue.YAxisAng = pPlayerCam->GetCamAngY();
	_ThrowingBallInitValue.powerRate = shootPowerPCT;
	return _ThrowingBallInitValue;
}
