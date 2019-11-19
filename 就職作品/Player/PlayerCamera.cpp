#include "PlayerCamera.h"
#include"../GameScene/GameScene.h"		//�X�e�[�W�T�C�Y�̏�񋤗L�̂���

//=====================================
//public���\�b�h
//=====================================
PlayerCamera::PlayerCamera(int Scrw, int Scrh, HWND Hwnd)
{
	hwnd = Hwnd;
	SCRw = Scrw;
	SCRh = Scrh;
	basePt.x = SCRw / 2;
	basePt.y = SCRh / 2;
	angX = 0, angY = 0;		//������
	ClientToScreen(hwnd, &basePt);
	SetCursorPos(basePt.x, basePt.y);
	ShowCursor(FALSE);			//�J�[�\����\�����Ȃ�	��FALSE�̉񐔂��J�E���g���Ă���̂ŕK�v�ȏ�ɌĂ΂Ȃ�
	D3DXMatrixIdentity(&billBoardMat);
	moveSpeed = 0.5;		//�ړ����x
}

PlayerCamera::~PlayerCamera()
{
	ShowCursor(TRUE);			//�J�[�\����\������	��TRUE�̉񐔂��J�E���g���Ă���̂ŕK�v�ȏ�ɌĂ΂Ȃ�
}

void PlayerCamera::Update(void)
{
	Move();
}

void PlayerCamera::SetCamera(void)
{
	D3DXMATRIX mView, mProj;


	POINT Pt;
	GetCursorPos(&Pt);					//���݂̃J�[�\���̈ʒu�������
	angY += (Pt.x - basePt.x) / 4.0f;	//�ŏ��̈ʒu�Ƃ̍������߁A�ړ��ʂ𒲐����Ă���

	angX += (Pt.y - basePt.y) / 4.0f;
	SetCursorPos(basePt.x, basePt.y);	//�J�[�\���ʒu���Z�b�g

	if (angX >= 70)
	{
		angX = 70;
	}

	if (angX <= -70)
	{
		angX = -70;
	}

	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(angY));				//�X������������]������

	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(angX));				//�X������������]������

	rotMat = rotMatX * rotMatY;

	D3DXVECTOR3 camTmpVec, camHead;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &rotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��
	D3DXVec3TransformCoord(&camHead, &D3DXVECTOR3(0, 1, 0), &rotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��


	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y, pos.z),	// �J�����̈ʒu	
		&(D3DXVECTOR3(pos.x, pos.y, pos.z) + camTmpVec),	// �J�����̎��_
		&camHead	// �J�����̓��̕���
	);

	//�ړ������𔲂��Ď��_�s��쐬
	D3DXMatrixLookAtLH(&billBoardMat,
		&D3DXVECTOR3(0, 0, 0),	// �J�����̈ʒu	
		&camTmpVec,	// �J�����̎��_
		&camHead	// �J�����̓��̕���
	);

	D3DXMatrixInverse(&billBoardMat, NULL, &billBoardMat);		//�r���{�[�h�p���_�s��

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRw / (float)SCRh, 1.0f, 2000.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}


float PlayerCamera::GetCamAngX(void)
{
	return angX;
}

float PlayerCamera::GetCamAngY(void)
{
	return angY;
}

D3DXMATRIX PlayerCamera::GetbillBoardMat(void)
{
	return billBoardMat;
}

D3DXVECTOR3 PlayerCamera::GetmoveVec(void)
{
	return moveVec;
}

D3DXVECTOR3 PlayerCamera::GetPos(void)
{
	return pos;
}

void PlayerCamera::PushPos(D3DXVECTOR3 *PushVec)
{
	pos += *PushVec;
}

void PlayerCamera::SetPos(D3DXVECTOR3 * SetPos)
{
	pos = *SetPos;
	pos.y = camHight;
}

//=====================================
//private���\�b�h
//=====================================
void PlayerCamera::Move(void)
{

	moveVec = D3DXVECTOR3(0, 0, 0);
	bool moveFlag = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY + 180));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY - 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(angY + 90));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0, 0, 1), &RotMat);
		moveVec += Vec;
		moveFlag = true;
	}

	D3DXVec3Normalize(&moveVec, &moveVec);			//�ړ��ʐ��K��

	moveVec *= moveSpeed;		//�ړ��X�s�[�h����

	if (moveFlag == true)
	{
		pos += moveVec;
	}

	//�X�e�[�W���E�̏���
	if (pos.z > stageBorder->Top)
	{
		pos.z += stageBorder->Top - pos.z;
	}

	if (pos.z < stageBorder->Bottom)
	{
		pos.z += stageBorder->Bottom - pos.z;
	}

	if (pos.x < stageBorder->Left)
	{
		pos.x += stageBorder->Left - pos.x;
	}

	if (pos.x > stageBorder->Right)
	{
		pos.x += stageBorder->Right - pos.x;
	}

}
