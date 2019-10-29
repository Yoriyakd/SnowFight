#include "Player.h"
#include"../Map/LoadStageData.h"
//#include"../GameScene/GameScene.h"

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

	D3DXVec3Normalize(&movePos, &movePos);			//�ړ��ʐ��K��

	movePos *= moveSpeed;		//�ړ��X�s�[�h����

	if (moveFlag)
	{
		pos += movePos;
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
	static float TimeCnt = 0;
	static const float MaxPowerTime = 3;		//�ő嗭�߂܂łɂ����鎞��

	if (remainingBalls > 0) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			LKyeFlag = true;
			TimeCnt++;
			//--------------------------------------------------
			//��ʋO�Օ\������
			//--------------------------------------------------
			float PowerPCT;
			if (TimeCnt > MaxPowerTime * GameFPS)
			{
				PowerPCT = 100;		//�ő嗭�߂̑���
			}
			else
			{
				PowerPCT = 30;		//�ő嗭�߂������̑���
			}
			
			SnowBallInitValue GhostTmp;
			GhostTmp.shootPos = pos;
			GhostTmp.shootPos.y += 3;							//���ˈʒu����(�ϐ���)
			GhostTmp.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
			GhostTmp.YAxisAng = pPlayerCam->GetCamAngY();
			GhostTmp.powerRate = PowerPCT;
			GhostTmp.id = PLAYER_ID;

			MakeGhostMat(&GhostTmp);

		}
		else
		{
			ghostMat.clear();	//�����ĂȂ��Ƃ��͔�\��
			if (LKyeFlag == true)
			{
				float PowerPCT;
				if (TimeCnt > MaxPowerTime * GameFPS)
				{
					PowerPCT = 100;		//�ő嗭�߂̑���
				}
				else
				{
					PowerPCT = 30;		//�ő嗭�߂������̑���
				}
				

				SnowBallInitValue ValueTmp;
				ValueTmp.shootPos = pos;
				ValueTmp.shootPos.y += 3;							//���ˈʒu����(�ϐ���)
				ValueTmp.XAxisAng = pPlayerCam->GetCamAngX() * -1;	//�J������X���p�x�����̂܂ܓn���Ə������-�Ȃ̂Ŕ��]�����Ă�
				ValueTmp.YAxisAng = pPlayerCam->GetCamAngY();
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
	float Power;
	D3DXVECTOR3 moveVec;
	D3DXMATRIX TmpMat, TmpRot;
	Power = ((snowBallInitValue->powerRate / 100)) * 5;

	D3DXMatrixTranslation(&TmpMat, snowBallInitValue->shootPos.x, snowBallInitValue->shootPos.y, snowBallInitValue->shootPos.z);			//���ˈʒu

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(snowBallInitValue->XAxisAng))), (Power * cos(D3DXToRadian(snowBallInitValue->XAxisAng))));

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(snowBallInitValue->YAxisAng));
	TmpMat = TmpRot * TmpMat;

	ghostMat.push_back(TmpMat);
	//----------------------------------
	//while���Œn�ʏՓ˂܂ŉ�
	//----------------------------------
	while (1)
	{
		D3DXMATRIX MoveMat;			//�ړ����I�������̍s��
		moveVec.y += -0.02f;

		D3DXMatrixTranslation(&MoveMat, moveVec.x, moveVec.y, moveVec.z);
		TmpMat = MoveMat * TmpMat;
		ghostMat.push_back(TmpMat);
		if (TmpMat._42 < 0)break;
	}
}

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	int StartBallCnt = 10;	//�X�^�[�g���̃{�[���̐� �v���C���[�̋����̃f�[�^���E���Ă��ē����悤�ɂ���

	moveSpeed = 0.5;		//�ړ����x
	mesh = resourceManager->GetXFILE("Player/player.x");

	remainingBalls = StartBallCnt;
	ballMesh = resourceManager->GetXFILE("commonObj/SnowBall.x");



	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�X�^�[�g�|�C���g
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
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//--------------------------------------------------------------
	//�쐬���̐�ʕ\��
	//--------------------------------------------------------------
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	D3DXMatrixTranslation(&ballMat, 0, 2, 3);		//�v���C���[�Ƃǂꂮ�炢����Ă��邩
	D3DXMatrixRotationY(&rotMat, D3DXToRadian(pPlayerCam->GetCamAngY()));
	ballMat = ballScalMat * ballMat * rotMat * mat;
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
