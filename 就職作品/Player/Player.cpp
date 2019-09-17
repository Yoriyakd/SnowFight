#include "Player.h"

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
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		movePos += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(camAngY + 90));
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

int Player::ShootSnowball(void)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		snowBall_P.push_back(new SnowBall(pos, camAngY));
	}
	return 0;		//�c�e����n��
}

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	moveSpeed = 0.5;		//test
	mesh = resourceManager->GetXFILE("Player/player.x");
	
	camAngX = 0, camAngY = 0;		//������

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mat);

	//--------------------------------------------------------------
	//�J�������̏�����
	//--------------------------------------------------------------
	basePt.x = SCRW / 2;
	basePt.y = SCRH / 2;

	ClientToScreen(hwnd, &basePt);
	SetCursorPos(basePt.x, basePt.y);

	
}

Player::~Player()
{
	for (unsigned int i = 0; i < snowBall_P.size(); i++)
	{
		delete snowBall_P[i];
	}
	snowBall_P.clear();
}

bool Player::Update(void)
{
	Move();
	ShootSnowball();
	//D3DXMatrixTranslation(&transMat, pos.x, pos.y, pos.z);		//��
	//D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);		//��
	//mat = transMat * mat;		//���������(0, 0, 10)�̂��������������悤�Ȍ`�ɂȂ�	�ω������������̂ݍ����Ƃ��ł������邩��
	

	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);		
	
	for (unsigned int i = 0; i < snowBall_P.size(); i++)
	{
		if (snowBall_P[i]->Update() == false)
		{
			delete snowBall_P[i];
			snowBall_P.erase(snowBall_P.begin() + i);
			i--;
		}
	}

	return true;
}

void Player::SetCamera(void)
{
	D3DXMATRIX mView, mProj;

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		AngY++;
	}*/

	

	POINT Pt;					
	GetCursorPos(&Pt);					//���݂̃J�[�\���̈ʒu�������
	camAngY += (Pt.x - basePt.x) / 4.0f;	//�ŏ��̈ʒu�Ƃ̍������߁A�ړ��ʂ𒲐����Ă���
	
	camAngX += (Pt.y - basePt.y) / 4.0f;
	SetCursorPos(basePt.x, basePt.y);	//�J�[�\���ʒu���Z�b�g

	if (camAngX >= 70)
	{
		camAngX = 70;
	}
	
	if (camAngX <= -70)
	{
		camAngX = -70;
	}

	D3DXMatrixRotationY(&camRotMatY, D3DXToRadian(camAngY));				//�X������������]������
	
	D3DXMatrixRotationX(&camRotMatX, D3DXToRadian(camAngX));				//�X������������]������

	camRotMat = camRotMatX * camRotMatY;

	D3DXVECTOR3 camTmpVec;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &camRotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y + 5, pos.z ),	// �J�����̈ʒu						//�J�����̕ϐ���p�ӂ�����������
		&(D3DXVECTOR3(pos.x, pos.y + 5, pos.z) + camTmpVec),	// �J�����̎��_		//�J�����̕ϐ���p�ӂ�����������	
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);
	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void Player::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
	for (unsigned int i = 0; i < snowBall_P.size(); i++)
	{
		snowBall_P[i]->Draw();
	}
}
