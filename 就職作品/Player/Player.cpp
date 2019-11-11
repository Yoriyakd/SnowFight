#include "Player.h"
#include"../Map/LoadStageData.h"
#include"../GameScene/GameScene.h"

extern ResourceManager *resourceManager;
const float Player::MaxPowerTime = 1.5f;

//=====================================
//private���\�b�h
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

	D3DXVec3Normalize(&moveVec, &moveVec);			//�ړ��ʐ��K��

	moveVec *= moveSpeed;		//�ړ��X�s�[�h����

	if (moveFlag)
	{
		pos += moveVec;
	}

	//�X�e�[�W���E�̏���
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

			////--------------------------------------------------
			////�r��]����
			////--------------------------------------------------
			//static const float MaxAng = 120;
			//armAng = MaxAng * (timeCnt / (MaxPowerTime * GameFPS));

			//D3DXMatrixRotationX(&armRotMatXR, D3DXToRadian(-armAng));

		}
		else
		{
			ghostMat.clear();	//�����ĂȂ��Ƃ��͔�\��
			if (LKyeFlag == true)
			{
				MakeSnowBallInitValue();
				snowBallManager->SetSnowBall(&MakeSnowBallInitValue());
				timeCnt = 0;
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
			if (MakeingTimeCnt >= MakeTime * GameFPS)		//����Ă������Ԃ����̂ɕK�v�Ȏ��Ԉȏ�Ȃ�쐬����
			{
				remainingBalls++;
			}
			else
			{
				//����Ȃ���Ή���
				//SnowFrag�G�t�F�N�g�Ă�
				effectManager->snowFrag.push_back(new SnowFrag((D3DXVECTOR3(ballMat._41, ballMat._42, ballMat._43))));
			}
			RKyeFlag = false;
			MakeingTimeCnt = 0;		//���Z�b�g
			D3DXMatrixScaling(&ballScalMat, 0.0f, 0.0f, 0.0f);
		}
	}
}

void Player::MakeGhostMat(SnowBallInitValue *snowBallInitValue)
{
	ghostMat.clear();	//������

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
		moveVec.y += Gravity;

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

	D3DXVec3TransformCoord(&ShootOffset, &shootOffset, &rotMat);	//��]���l�������x�N�g���쐬

	_SnowBallInitValue.shootPos = pos + ShootOffset;
	_SnowBallInitValue.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
	_SnowBallInitValue.YAxisAng = pPlayerCam->GetCamAngY();
	_SnowBallInitValue.powerRate = shootPowerPCT;
	_SnowBallInitValue.id = PLAYER_ID;
	return _SnowBallInitValue;
}

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	//--------------------------------------------------------------
	//�v���C���[������
	//--------------------------------------------------------------
	int StartBallCnt = 10;	//�X�^�[�g���̃{�[���̐� �v���C���[�̋����̃f�[�^���E���Ă��ē����悤�ɂ���

	moveSpeed = 0.5;		//�ړ����x
	mesh = resourceManager->GetXFILE("player.x");

	remainingBalls = StartBallCnt;
	
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�X�^�[�g�|�C���g
	D3DXMatrixIdentity(&mat);

	GhostTex = resourceManager->GetTexture("Locus.png", 64, 64, NULL);

	//--------------------------------------------------------------
	//�r
	//--------------------------------------------------------------
	//armMeshR = resourceManager->GetXFILE("ArmR.x");
	//D3DXMatrixTranslation(&armOffsetMatR, 1.0f, -2.0f, 0.0f);		//�v���C���[�̌��_����̋���
	
	/*armAng = 0.0f;
	D3DXMatrixRotationX(&armRotMatXR, D3DXToRadian(-armAng));*/

	//--------------------------------------------------------------
	//���
	//--------------------------------------------------------------
	ballMesh = resourceManager->GetXFILE("SnowBall.x");
	D3DXMatrixTranslation(&ballOffsetMat, 0, 2, 3);		//�v���C���[�Ƃǂꂮ�炢����Ă��邩
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
	//�v���C���[�̍s��쐬
	//-------------------------------------------------------
	D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(pPlayerCam->GetCamAngY()));
	mat = rotMat * transMat;		//Y���̂�

	//-------------------------------------------------------
	//�r�̍s��쐬
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
	 



	if (GetAsyncKeyState('O') & 0x8000)		//�f�o�b�O ��
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
	//�v���C���[�\��
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//�r�\��
	//--------------------------------------------------------------
	/*lpD3DDevice->SetTransform(D3DTS_WORLD, &armMatR);
	DrawMesh(&armMeshR);*/

	//--------------------------------------------------------------
	//�쐬���̐�ʕ\��
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O

	ballMat = ballScalMat * ballOffsetMat * mat;
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
		if (ghostMat.size() == 0)
		{
			break;
		}
		vertex[0].Tex = D3DXVECTOR2(0.0f, (float)i / (ghostMat.size() - 1));
		vertex[1].Tex = D3DXVECTOR2(1.0f, (float)i / (ghostMat.size() - 1));
		vertex[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (ghostMat.size() - 1));
		vertex[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (ghostMat.size() - 1));


		D3DXVec3TransformCoord(&vertex[0].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f),&ghostMat[i]);		//�|�C���^�^�Ő錾���Ă�����Pos�ڒl��nan�ɂȂ��Ă���
		D3DXVec3TransformCoord(&vertex[1].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &ghostMat[i]);
		D3DXVec3TransformCoord(&vertex[2].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &ghostMat[i + 1]);
		D3DXVec3TransformCoord(&vertex[3].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &ghostMat[i + 1]);

		lpD3DDevice->SetTexture(0, GhostTex);
		D3DXMATRIX IdenMat;
		D3DXMatrixIdentity(&IdenMat);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));
	}



	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���Z�����I�t
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Z�o�b�t�@�������݃I��

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
