#include "Player.h"
#include"../GameScene/GameScene.h"
#include"../DirectX/Direct3D.h"

//=====================================
//publicメソッド
//=====================================

Player::Player() :remainingBalls(START_BALL_CNT), carryFlag(false), carryObjID(NUM_ITEM_Dummy), makingTimeCnt(0.0f), canMakeSnowBallFlag(true){
	//--------------------------------------------------------------
	//プレイヤー初期化
	//--------------------------------------------------------------
	ghost_SnowTex = GetResource.GetTexture(ThrowGhostSnow_Tex);
	ghost_DecoTex = GetResource.GetTexture(ThrowGhostDeco_Tex);
	

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

	carryItem = new CarryItem(&armRMat);
	playerState = new PlayerStateIdle(&armLOffsetMat, &armROffsetMat);

	carryItem->SetNowCarryItemPointer(&carryObjID);
}

Player::~Player()
{
	delete playerState;
	delete carryItem;
}

bool Player::Update(PickUpInstructions &PickUpInstructions)
{
	pos = GetPlayerCam.GetPos();		//カメラの座標をセット

	//-----------------------------------------------------
	//デコレーション周り
	//-----------------------------------------------------
	
	if (GetDecorationManager.CheckForCanPicUp(&pos) == true)			//拾えるかのチェックだけ		
	{
		//運んでいるときは持ち運べない予定なので、はこんでいるときの指示は別に出す方がよさそう

		PickUpInstructions.TurnOnDisplay();		//拾える時画面に指示を表示
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		{
			if (carryFlag == false)		//今運んでいないなら
			{
				PickUpDecoration();
				canMakeSnowBallFlag = false;		//拾える状態では雪玉作成より拾うことを優先する
			}
			else
			{
				canMakeSnowBallFlag = true;
			}
		}
	}
	else
	{
		PickUpInstructions.TurnOffDisplay();
		canMakeSnowBallFlag = true;
	}
	
	if (carryFlag == false)		//Itemを運んでおらず、雪玉を持っていたら雪玉を手に持つ
	{
		if (remainingBalls > 0)
		{
			carryObjID = SNOW_BALL;
			carryItem->SetDisplayFlag(true);
		}
		else
		{
			carryItem->SetDisplayFlag(false);
		}
	}
	else
	{
		carryItem->SetDisplayFlag(true);
	}

	//-----------------------------------------------------
	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(GetPlayerCam.GetCamAngY()));		//カメラの回転から行列作成
	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(GetPlayerCam.GetCamAngX()));		//カメラの回転から行列作成

	//-------------------------------------------------------
	//靴の行列作成
	//-------------------------------------------------------
	shoesMat = shoesOffsetMat * shoesRotMatX * rotMatY * transMat;		//プレイヤーのX軸は回転しない

	//-------------------------------------------------------
	//腕の行列作成とplayerState管理
	//-------------------------------------------------------
	if (playerState != nullptr)
	{
		PlayerStateBase *NextAnime;
		NextAnime = playerState->Action(&armLOffsetMat, &armROffsetMat);
		if (NextAnime != nullptr)
		{
			delete playerState;
			playerState = NextAnime;
		}
	}

	MakeGhostMat();
	
	armRMat = armROffsetMat * rotMatX * rotMatY * transMat;		//カメラからの距離の距離の行列にカメラの行列から作った行列を合成してプレイヤーについていかせる
	armLMat = armLOffsetMat * rotMatX * rotMatY * transMat;
	 
	//-------------------------------------------------------
	//作成中の雪玉行列作成
	//-------------------------------------------------------
	ballMat = ballScalMat * ballOffsetMat * rotMatY * transMat;

	//-------------------------------------------------------
	//保持している雪玉、デコレーションの行列
	//-------------------------------------------------------
	carryItem->Updata();

	if (remainingBalls > 999)
	{
		remainingBalls = 999;			//カンストチェック
	}
	
	return true;
}


void Player::Draw(void)
{
	//--------------------------------------------------------------
	//軌道の表示
	//--------------------------------------------------------------
	Direct3D::GetInstance().GetD3DDevice()->SetFVF(FVF_VERTEX);
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//加算合成オン
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Zバッファ書き込みオフ

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

		if (carryFlag == true)
		{
			Direct3D::GetInstance().GetD3DDevice()->SetTexture(0, ghost_DecoTex);
		}
		else
		{
			Direct3D::GetInstance().GetD3DDevice()->SetTexture(0, ghost_SnowTex);
		}

		D3DXMATRIX IdenMat;
		D3DXMatrixIdentity(&IdenMat);
		Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &IdenMat);

		Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));
	}


	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン
	   
	//--------------------------------------------------------------
	//作成中の雪玉表示
	//--------------------------------------------------------------
	Direct3D::GetInstance().GetD3DDevice()->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 125), 1.0f, 0);		//Zバッファクリア	※GameSceneで最後に呼ぶ

	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング

	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);

	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//--------------------------------------------------------------
	//靴表示
	//--------------------------------------------------------------
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &shoesMat);
	DrawMesh(&shoesMesh);

	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//腕表示
	//--------------------------------------------------------------
	Direct3D::GetInstance().GetD3DDevice()->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 125), 1.0f, 0);		//Zバッファクリア	※GameSceneで最後に呼ぶ

	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &armRMat);
	DrawMesh(&armRMesh);

	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &armLMat);
	DrawMesh(&armLMesh);

	carryItem->Draw();
}

int Player::GetRemainingBalls()
{
	return remainingBalls;
}


const D3DXVECTOR3 Player::GetPlayerPos(void)
{
	return pos;
}

const D3DXMATRIX Player::GetMat(void)
{
	D3DXMATRIX TmpMat;

	TmpMat = rotMatX * rotMatY * transMat;
	return TmpMat;
}

void Player::GetCollisionSphere(CollisionSphere *CollisionSphere)
{
	CollisionSphere->pos = pos;
	CollisionSphere->radius = CollisionRadius;

}

//=====================================
//privateメソッド
//=====================================

void Player::Throw(const float PowerPct)
{
	GetSound.Play2D(Throw_Sound);
	if (carryFlag == true)			//デコレーションを運んでいる状態ではデコレーションを投げる
	{
		carryFlag = false;

		D3DXVECTOR3 DropPoinOffset;

		DropPoinOffset = D3DXVECTOR3(0, 2.0f, 5.0f);		//プレイヤーの少し前に落とすようにする
		D3DXVec3TransformCoord(&DropPoinOffset, &DropPoinOffset, &rotMatY);	//回転を考慮したベクトル作成

		GetDecorationManager.Throw(carryObjID, &MakeThrowValue(PowerPct));
		return;
	}

	GetSnowBallManager.SetSnowBall(&MakeThrowValue(PowerPct), PLAYER_ID);
	remainingBalls--;		//発射したら残数を1減らす
}

bool Player::IsThrowAnything()
{
	if (remainingBalls > 0)return true;
	if (carryFlag == true)return true;
	return false;
}

void Player::SetShootPower(float ShootPower)
{
	 shootPower = ShootPower;
}

void Player::MakeBallStart()
{
	static bool RKyeFlag = false;

	static float ballSize = 0;

	GetSound.Play2D(MakingSnowBall_Sound);

	shootPower = 0;
	carryItem->SetDisplayFlag(false);			//タイミングの調整とplayerに消える瞬間がみえないようにするアニメ挿入☆

	if (GetPlayerCam.GetHasPosed() == true)
	{
		RKyeFlag = true;

		makingTimeCnt++;
		//--------------------------------------------
		//靴のアニメーションを開始する
		//--------------------------------------------

		ShoesMakeBallAnime(true);

		ballSize = makingTimeCnt / (CREATION_SNOWBALL_TIME_SECOND * GAME_FPS) * MaxBallScal;			//時間経過で大きくなる

		D3DXMatrixScaling(&ballScalMat, ballSize, ballSize, ballSize);

		if (makingTimeCnt >= CREATION_SNOWBALL_TIME_SECOND * GAME_FPS)		//作っていた時間が作るのに必要な時間以上なら作成完了
		{
			remainingBalls++;
			makingTimeCnt = 0;		//リセット
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);

			AddSnowBallUI::GetInstance().AddSnowBall();
			GetSound.Play2D(FinishedMakingSnowBall_Sound);
			GetSound.Stop(MakingSnowBall_Sound);
		}
	}
}

void Player::MakeBallEnd()
{
	GetSound.Stop(MakingSnowBall_Sound);
	Effect.NewSnowFrag((D3DXVECTOR3(ballMat._41, ballMat._42, ballMat._43)));	
	makingTimeCnt = 0;		//リセット
	D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);

	carryItem->SetDisplayFlag(true);
	//--------------------------------------------
	//カメラと靴のアニメーションを終了する
	//--------------------------------------------
	ShoesMakeBallAnime(false);
	
}

bool Player::CanMakeSnowBall()
{
	return canMakeSnowBallFlag;
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

void Player::MakeGhostMat()
{
	std::vector<D3DXMATRIX>().swap(ghostMat);		//メモリ開放
	if (shootPower == 0)return;

	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;

	ThrowingInitValue TmpThrowingInitValue;

	TmpThrowingInitValue = MakeThrowValue(shootPower);

	moveVec = ThrowingInit(&TmpThrowingInitValue, &TmpMat);

	D3DXMatrixTranslation(&TmpMat, TmpThrowingInitValue.shootPos.x, TmpThrowingInitValue.shootPos.y, TmpThrowingInitValue.shootPos.z);			//発射位置

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(TmpThrowingInitValue.YAxisAng));		//発射元の角度から行列作成
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

ThrowingInitValue Player::MakeThrowValue(const float PowerPct)
{
	D3DXVECTOR3 ShootOffset;	//回転を考慮した座標を入れる
	ThrowingInitValue _ThrowingBallInitValue;

	D3DXVec3TransformCoord(&ShootOffset, &shootOffset, &rotMatY);	//回転を考慮したベクトル作成

	_ThrowingBallInitValue.shootPos = pos + ShootOffset;
	_ThrowingBallInitValue.XAxisAng = GetPlayerCam.GetCamAngX() * -1 + ADD_SHOOT_ANG;	//カメラのX軸角度をそのまま渡すと上向きが-なので反転させてる
	_ThrowingBallInitValue.YAxisAng = GetPlayerCam.GetCamAngY();
	_ThrowingBallInitValue.powerRate = PowerPct;
	return _ThrowingBallInitValue;
}

void Player::PickUpDecoration()
{
	carryObjID = GetDecorationManager.PickUp(&pos);				//拾う	近くに2つ以上アイテムがあると配列番号が若いものが優先して拾われてしまう
	carryFlag = true;
	GetSound.Play2D(PickUp_Sound);
}

