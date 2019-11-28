#include "Player.h"
#include"../Map/LoadStageData.h"
#include"../GameScene/GameScene.h"

extern ResourceManager *resourceManager;
const float Player::MaxPowerTime = 1.5f;

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	//--------------------------------------------------------------
	//�v���C���[������
	//--------------------------------------------------------------
	int StartBallCnt = 10;	//�X�^�[�g���̃{�[���̐�


	remainingBalls = StartBallCnt;

	GhostTex = resourceManager->GetTexture("Locus.png", 64, 64, NULL);
	carryFlag = false;

	//--------------------------------------------------------------
	//�C
	//--------------------------------------------------------------
	shoesMesh = resourceManager->GetXFILE("Shoes.x");
	D3DXMatrixTranslation(&shoesOffsetMat, 0, -5, 0);			//�v���C���[�Ƃ����痣����

	//--------------------------------------------------------------
	//�r
	//--------------------------------------------------------------
	armRMesh = resourceManager->GetXFILE("ArmR.x");

	D3DXMATRIX TmpRotZ, TmpTransMat;
	D3DXMatrixTranslation(&TmpTransMat, 1.5f, -1.5f, 3.0f);		//�v���C���[�̌��_����̋���
	

	D3DXMatrixRotationZ(&TmpRotZ, D3DXToRadian(30));
	armROffsetMat = TmpRotZ * TmpTransMat;

	armLMesh = resourceManager->GetXFILE("ArmL.x");
	D3DXMatrixTranslation(&armLOffsetMat, -2.5, -1.0, 0.0f);
	
	//--------------------------------------------------------------
	//���
	//--------------------------------------------------------------
	ballMesh = resourceManager->GetXFILE("SnowBall.x");
	D3DXMatrixTranslation(&ballOffsetMat, 0, -3, 3);		//�v���C���[�Ƃ����痣����
}

Player::~Player()
{
	delete ArmRAnime;
}

bool Player::Update(SnowBallManager *snowBallManager)
{
	D3DXVECTOR3 NewPos;
	NewPos = pPlayerCam->GetPos();		//�J�����̍��W���Z�b�g

	if (pos == NewPos)		//�����Ă��邩�ǂ�������
	{
		pos = NewPos;
		walkFlag = true;
		//ArmLAnime = new ArmLWalkAnime()		//��
	}
	else
	{
		pos = NewPos;
		walkFlag = false;
	}

	//-----------------------------------------------------
	
	if (decorationManager->CheckForCanPicUp(&pos) == true)			//�E���邩�̃`�F�b�N����		
	{//�^��ł���Ƃ��͎����^�ׂȂ��\��Ȃ̂ŁA�͂���ł���Ƃ��̎w���͕ʂɏo�������悳����
		pickUpInstructions->TurnOnDisplay();		//�E���鎞��ʂɎw����\��
		if (carryFlag == false)		//���^��ł��Ȃ��Ȃ�
		{
			if (GetAsyncKeyState('F') & 0x8000)
			{
				carryDecorationID = decorationManager->PickUp(&pos);				//�E��	�߂���2�ȏ�A�C�e��������Ɣz��ԍ����Ⴂ���̂��D�悵�ďE���Ă��܂�
				carryFlag = true;
			}
		}
	}
	else
	{
		pickUpInstructions->TurnOffDisplay();
	}

	if (carryFlag == true)
	{
		if (GetAsyncKeyState('Q') & 0x8000)		//F�ł������悤��
		{
			carryFlag = false;

			D3DXVECTOR3 DropPoinOffset;

			DropPoinOffset = D3DXVECTOR3(0, 2.0f, 5.0f);		//�v���C���[�̂̏����O�ɗ��Ƃ��悤�ɂ���
			D3DXVec3TransformCoord(&DropPoinOffset, &DropPoinOffset, &rotMatY);	//��]���l�������x�N�g���쐬

			decorationManager->Drop(&(pos + DropPoinOffset), carryDecorationID);
		}
	}




	//pos = D3DXVECTOR3(0, 5, 0);		//�f�o�b�N�p��

	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(pPlayerCam->GetCamAngY()));		//�J�����̉�]����s��쐬
	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(pPlayerCam->GetCamAngX()));		//�J�����̉�]����s��쐬


	ShootSnowball(snowBallManager);
	MakeBall();

	//-------------------------------------------------------
	//�C�̍s��쐬
	//-------------------------------------------------------
	shoesMat = shoesOffsetMat * rotMatY * transMat;		//Y���̂݉�]

	//-------------------------------------------------------
	//�r�̍s��쐬
	//-------------------------------------------------------
	if (ArmRAnime != nullptr)
	{
		ArmAnimeBase *NextAnime;
		NextAnime = ArmRAnime->Anime(&armROffsetMat);
		if (NextAnime != nullptr)
		{
			delete ArmRAnime;
			ArmRAnime = NextAnime;
		}
	}
	
	armRMat = armROffsetMat * rotMatX * rotMatY * transMat;		//�J��������̋����̋����̍s��ɃJ�����̍s�񂩂������s����������ăv���C���[�ɂ��Ă�������
	armLMat = armLOffsetMat * rotMatY * transMat;
	 
	//-------------------------------------------------------
	//�쐬���̐�ʍs��쐬
	//-------------------------------------------------------
	ballMat = ballScalMat * ballOffsetMat * rotMatY * transMat;

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

void Player::SetCamera(void)
{
	

}

void Player::Draw(void)
{
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
	lpD3DDevice->SetTransform(D3DTS_WORLD, &armRMat);
	DrawMesh(&armRMesh);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &armLMat);
	DrawMesh(&armLMesh);

	//--------------------------------------------------------------
	//�쐬���̐�ʕ\��
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O

	lpD3DDevice->SetTransform(D3DTS_WORLD, &ballMat);
	DrawMesh(&ballMesh);

	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

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

		lpD3DDevice->SetTexture(0, GhostTex);
		D3DXMATRIX IdenMat;
		D3DXMatrixIdentity(&IdenMat);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));
	}


	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���Z�����I�t
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Z�o�b�t�@�������݃I��

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
//private���\�b�h
//=====================================

void Player::ShootSnowball(SnowBallManager *snowBallManager)
{
	static bool LKyeFlag = false;
	static bool AnimeFlag = false;

	if (remainingBalls > 0) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			LKyeFlag = true;
			timeCnt++;

			if (timeCnt > MaxPowerTime * GameFPS)
			{
				shootPowerPCT = 80;		//�ő嗭�߂̑���
			}
			else
			{
				shootPowerPCT = 30 + 50 * (timeCnt / (MaxPowerTime * GameFPS));		//30��50�͉��ƂȂ��Ō��߂Ă���
			}

			//--------------------------------------------------
			//��ʋO�Օ\������
			//--------------------------------------------------
			MakeGhostMat(&MakeSnowBallInitValue());
		
			//�r�A�j���[�V����
			if (AnimeFlag == false)
			{
				AnimeFlag = true;
				ArmRAnime = new WindUpRAnime(&armROffsetMat);
			}

		}
		else
		{
			std::vector<D3DXMATRIX>().swap(ghostMat);		//�������J��
			if (LKyeFlag == true)
			{
				MakeSnowBallInitValue();
				snowBallManager->SetSnowBall(&MakeSnowBallInitValue());
				timeCnt = 0;
				LKyeFlag = false;
				remainingBalls--;		//���˂�����c����1���炷

				//�r�A�j���[�V����
				AnimeFlag = false;
				ArmRAnime = new ThrowRAnime();
			}
		}
	}
}

void Player::MakeBall()
{
	static bool RKyeFlag = false;
	static float MakeingTimeCnt = 0;
	static const float MakeTime = 1.5;		//�쐬�ɕK�v�Ȏ���
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

		if (MakeingTimeCnt >= MakeTime * GameFPS)		//����Ă������Ԃ����̂ɕK�v�Ȏ��Ԉȏ�Ȃ�쐬����
		{
			remainingBalls++;
			MakeingTimeCnt = 0;		//���Z�b�g
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
		}
	}
	else
	{
		if (RKyeFlag == true)
		{
			//SnowFrag�G�t�F�N�g�Ă�
			effectManager->snowFrag.push_back(new SnowFrag((D3DXVECTOR3(ballMat._41, ballMat._42, ballMat._43))));

			RKyeFlag = false;
			MakeingTimeCnt = 0;		//���Z�b�g
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
		}
	}
}

void Player::MakeGhostMat(SnowBallInitValue *snowBallInitValue)
{
	std::vector<D3DXMATRIX>().swap(ghostMat);		//�������J��

	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;


	moveVec = SnowBallInit(snowBallInitValue, &TmpMat);

	D3DXMatrixTranslation(&TmpMat, snowBallInitValue->shootPos.x, snowBallInitValue->shootPos.y, snowBallInitValue->shootPos.z);			//���ˈʒu

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(snowBallInitValue->YAxisAng));		//���ˌ��̊p�x����s��쐬
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

SnowBallInitValue Player::MakeSnowBallInitValue()
{
	D3DXVECTOR3 ShootOffset;	//��]���l���������W������
	SnowBallInitValue _SnowBallInitValue;

	D3DXVec3TransformCoord(&ShootOffset, &shootOffset, &rotMatY);	//��]���l�������x�N�g���쐬

	_SnowBallInitValue.shootPos = pos + ShootOffset;
	_SnowBallInitValue.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
	_SnowBallInitValue.YAxisAng = pPlayerCam->GetCamAngY();
	_SnowBallInitValue.powerRate = shootPowerPCT;
	_SnowBallInitValue.id = PLAYER_ID;
	return _SnowBallInitValue;
}
