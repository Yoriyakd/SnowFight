#include "Player.h"
#include"../GameScene/GameScene.h"

extern ResourceManager *resourceManager;


//=====================================
//public���\�b�h
//=====================================

Player::Player() :remainingBalls(StartBallCnt), HP(StartHP), carryFlag(false), carryDecorationID(NUM_ITEM){
	//--------------------------------------------------------------
	//�v���C���[������
	//--------------------------------------------------------------
	ghost_SnowTex = GetResource.GetTexture(ThrowGhostSnow_Tex);
	ghost_DecoTex = GetResource.GetTexture(ThrowGhostDeco_Tex);
	

	//--------------------------------------------------------------
	//�C
	//--------------------------------------------------------------
	shoesMesh = GetResource.GetXFILE(Shoes_M);
	D3DXMatrixTranslation(&shoesOffsetMat, 0, -5, 0);			//�v���C���[�Ƃ����痣����
	D3DXMatrixRotationX(&shoesRotMatX, D3DXToRadian(0));

	//--------------------------------------------------------------
	//�r
	//--------------------------------------------------------------
	armLMesh = GetResource.GetXFILE(ArmL_M);
	armRMesh = GetResource.GetXFILE(ArmR_M);

	D3DXMATRIX TmpRotZ, TmpRotX, TmpTransMat;

	D3DXMatrixTranslation(&TmpTransMat, -1.8f, -1.5f, -2.0f);
	D3DXMatrixRotationZ(&TmpRotZ, D3DXToRadian(-90));
	D3DXMatrixRotationX(&TmpRotX, D3DXToRadian(90));
	armLOffsetMat = TmpRotZ * TmpRotX * TmpTransMat;


	D3DXMatrixTranslation(&TmpTransMat, 1.8f, -1.5f, 3.0f);		//�v���C���[�̌��_����̋���
	D3DXMatrixRotationZ(&TmpRotZ, D3DXToRadian(30));
	armROffsetMat = TmpRotZ * TmpTransMat;

	//--------------------------------------------------------------
	//���
	//--------------------------------------------------------------
	ballMesh = GetResource.GetXFILE(SnowBall_M);
	D3DXMatrixTranslation(&ballOffsetMat, 0.0f, -3.0f, 1.5f);		//�v���C���[�Ƃ����痣����

	//carryItem = new CarryItem(&armRMat);
	playerState = new PlayerStateIdle(&armLOffsetMat, &armROffsetMat);
}

Player::~Player()
{
	delete playerState;
	//delete carryItem;
}

bool Player::Update(PickUpInstructions &PickUpInstructions)
{
	pos = GetPlayerCam.GetPos();		//�J�����̍��W���Z�b�g
	//pos = D3DXVECTOR3(100, 5, 30);		//�f�o�b�N�p��

	//-----------------------------------------------------
	//�f�R���[�V��������
	//-----------------------------------------------------
	if (GetDecorationManager.CheckForCanPicUp(&pos) == true)			//�E���邩�̃`�F�b�N����		
	{//�^��ł���Ƃ��͎����^�ׂȂ��\��Ȃ̂ŁA�͂���ł���Ƃ��̎w���͕ʂɏo�������悳����
		PickUpInstructions.TurnOnDisplay();		//�E���鎞��ʂɎw����\��
		if (carryFlag == false)		//���^��ł��Ȃ��Ȃ�
		{
			if (GetAsyncKeyState('F') & 0x8000)
			{
				carryDecorationID = GetDecorationManager.PickUp(&pos);				//�E��	�߂���2�ȏ�A�C�e��������Ɣz��ԍ����Ⴂ���̂��D�悵�ďE���Ă��܂�
				carryFlag = true;
			}
		}
	}
	else
	{
		PickUpInstructions.TurnOffDisplay();
	}

	//-----------------------------------------------------
	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(GetPlayerCam.GetCamAngY()));		//�J�����̉�]����s��쐬
	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(GetPlayerCam.GetCamAngX()));		//�J�����̉�]����s��쐬


	MakeBall();

	//-------------------------------------------------------
	//�C�̍s��쐬
	//-------------------------------------------------------
	shoesMat = shoesOffsetMat * shoesRotMatX * rotMatY * transMat;		//�v���C���[��X���͉�]���Ȃ�

	//-------------------------------------------------------
	//�r�̍s��쐬
	//-------------------------------------------------------
	if (playerState != nullptr)
	{
		PlayerStateBase *NextAnime;
		NextAnime = playerState->Anime(&armLOffsetMat, &armROffsetMat);
		if (NextAnime != nullptr)
		{
			delete playerState;
			playerState = NextAnime;
		}
	}

	MakeGhostMat();
	
	armRMat = armROffsetMat * rotMatX * rotMatY * transMat;		//�J��������̋����̋����̍s��ɃJ�����̍s�񂩂������s����������ăv���C���[�ɂ��Ă�������
	armLMat = armLOffsetMat * rotMatX * rotMatY * transMat;
	 
	//-------------------------------------------------------
	//�쐬���̐�ʍs��쐬
	//-------------------------------------------------------
	ballMat = ballScalMat * ballOffsetMat * rotMatY * transMat;

	//-------------------------------------------------------
	//�ێ����Ă����ʁA�f�R���[�V�����̍s��
	//-------------------------------------------------------
	//carryItem->Updata();

	if (GetAsyncKeyState('O') & 0x8000)		//�f�o�b�O ��
	{
		remainingBalls += 10;
	}

	if (remainingBalls > 999)
	{
		remainingBalls = 999;			//�J���X�g�`�F�b�N
	}
	
	return true;
}


void Player::Draw(void)
{
	//--------------------------------------------------------------
	//�O���̕\��
	//--------------------------------------------------------------
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//�t�H�O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�J�����O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//���Z�����I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Z�o�b�t�@�������݃I�t

	VERTEX vertex[4];

	vertex[0].Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(128, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(128, 255, 255, 255);

	for (unsigned int i = 0; i < (ghostMat.size() - 1); i++)
	{
		if (ghostMat.size() == 0)		//�O�Ղ�����Ă��Ȃ����͕`�悵�Ȃ�
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
			lpD3DDevice->SetTexture(0, ghost_DecoTex);
		}
		else
		{
			lpD3DDevice->SetTexture(0, ghost_SnowTex);
		}

		D3DXMATRIX IdenMat;
		D3DXMatrixIdentity(&IdenMat);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));
	}


	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���Z�����I�t
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Z�o�b�t�@�������݃I��
	   
	//--------------------------------------------------------------
	//�쐬���̐�ʕ\��
	//--------------------------------------------------------------
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 125), 1.0f, 0);		//Z�o�b�t�@�N���A	��GameScene�ōŌ�ɌĂ�

	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O

	lpD3DDevice->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);

	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//--------------------------------------------------------------
	//�C�\��
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &shoesMat);
	DrawMesh(&shoesMesh);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//�r�\��
	//--------------------------------------------------------------
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 125), 1.0f, 0);		//Z�o�b�t�@�N���A	��GameScene�ōŌ�ɌĂ�

	lpD3DDevice->SetTransform(D3DTS_WORLD, &armRMat);
	DrawMesh(&armRMesh);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &armLMat);
	DrawMesh(&armLMesh);

	//carryItem->Draw();
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

void Player::HitSnowBall()
{
	HP--;
}

int Player::GetHP()
{
	return HP;
}

//=====================================
//private���\�b�h
//=====================================

void Player::Throw(const float PowerPct)
{
	if (carryFlag == true)			//�f�R���[�V�������^��ł����Ԃł̓f�R���[�V�����𓊂���
	{
		carryFlag = false;

		D3DXVECTOR3 DropPoinOffset;

		DropPoinOffset = D3DXVECTOR3(0, 2.0f, 5.0f);		//�v���C���[�̏����O�ɗ��Ƃ��悤�ɂ���
		D3DXVec3TransformCoord(&DropPoinOffset, &DropPoinOffset, &rotMatY);	//��]���l�������x�N�g���쐬

		GetDecorationManager.Throw(carryDecorationID, &MakeThrowValue(PowerPct));
		return;
	}

	GetSnowBallManager.SetSnowBall(&MakeThrowValue(PowerPct), PLAYER_ID);
	remainingBalls--;		//���˂�����c����1���炷
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

void Player::MakeBall()
{
	static bool RKyeFlag = false;
	static float MakeingTimeCnt = 0;
	static float ballSize = 0;
	static bool AnimeFlag_MKB = false;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		GetPlayerCam.SetMakeSnowBallFlag(true);
		shootPower = 0;

		if (GetPlayerCam.GetHasPosed() == true)
		{
			RKyeFlag = true;

			MakeingTimeCnt++;
			//--------------------------------------------
			//�J�����ƌC�̃A�j���[�V�������J�n����
			//--------------------------------------------

			ShoesMakeBallAnime(true);

			if (AnimeFlag_MKB == false)
			{
				delete playerState;
				playerState = new MakeSnowBallAnime(&armLOffsetMat, &armROffsetMat);
				AnimeFlag_MKB = true;
			}

			//--------------------------------------------
			
			ballSize = MakeingTimeCnt / (MakeTime * GameFPS) * MaxBallScal;			//���Ԍo�߂ő傫���Ȃ�

			D3DXMatrixScaling(&ballScalMat, ballSize, ballSize, ballSize);

			if (MakeingTimeCnt >= MakeTime * GameFPS)		//����Ă������Ԃ����̂ɕK�v�Ȏ��Ԉȏ�Ȃ�쐬����
			{
				remainingBalls++;
				MakeingTimeCnt = 0;		//���Z�b�g
				D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
			}
		}
	}
	else
	{
		GetPlayerCam.SetMakeSnowBallFlag(false);
		ShoesMakeBallAnime(false);
		if (RKyeFlag == true)
		{
			//SnowFrag�G�t�F�N�g�Ă�
			Effect.NewSnowFrag((D3DXVECTOR3(ballMat._41, ballMat._42, ballMat._43)));

			RKyeFlag = false;
			MakeingTimeCnt = 0;		//���Z�b�g
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);

			//--------------------------------------------
			//�J�����ƌC�̃A�j���[�V�������I������
			//--------------------------------------------
			GetPlayerCam.SetMakeSnowBallFlag(false);

			AnimeFlag_MKB = false;
			delete playerState;
			playerState = new PlayerStateIdle(&armLOffsetMat, &armROffsetMat);
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

void Player::MakeGhostMat()
{
	std::vector<D3DXMATRIX>().swap(ghostMat);		//�������J��
	if (shootPower == 0)return;

	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;

	ThrowingInitValue TmpThrowingInitValue;

	TmpThrowingInitValue = MakeThrowValue(shootPower);

	moveVec = ThrowingInit(&TmpThrowingInitValue, &TmpMat);

	D3DXMatrixTranslation(&TmpMat, TmpThrowingInitValue.shootPos.x, TmpThrowingInitValue.shootPos.y, TmpThrowingInitValue.shootPos.z);			//���ˈʒu

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(TmpThrowingInitValue.YAxisAng));		//���ˌ��̊p�x����s��쐬
	TmpMat = TmpRot * TmpMat;

	ghostMat.push_back(TmpMat);
	//----------------------------------
	//while���Œn�ʏՓ˂܂ŉ�
	//----------------------------------
	while (1)
	{
		D3DXMATRIX MoveMat;			//�ړ����I�������̍s��
		moveVec.y += SnowBallGravity;

		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
		TmpMat = MoveMat * TmpMat;
		ghostMat.push_back(TmpMat);
		if (TmpMat._42 < 0)break;
	}
}

ThrowingInitValue Player::MakeThrowValue(const float PowerPct)
{
	D3DXVECTOR3 ShootOffset;	//��]���l���������W������
	ThrowingInitValue _ThrowingBallInitValue;

	D3DXVec3TransformCoord(&ShootOffset, &shootOffset, &rotMatY);	//��]���l�������x�N�g���쐬

	_ThrowingBallInitValue.shootPos = pos + ShootOffset;
	_ThrowingBallInitValue.XAxisAng = GetPlayerCam.GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
	_ThrowingBallInitValue.YAxisAng = GetPlayerCam.GetCamAngY();
	_ThrowingBallInitValue.powerRate = PowerPct;
	return _ThrowingBallInitValue;
}

