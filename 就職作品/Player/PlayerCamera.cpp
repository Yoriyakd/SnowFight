#include "PlayerCamera.h"
#include"../GameScene/GameScene.h"		//�X�e�[�W�T�C�Y�̏�񋤗L�̂���

//=====================================
//public���\�b�h
//=====================================

PlayerCamera::PlayerCamera()
{
	basePt.x = SCRW / 2;
	basePt.y = SCRH / 2;
	angX = 0, angY = 0;		//������
	ClientToScreen(hwnd, &basePt);		//basePt���X�N���[�����W�ɕϊ�����(��ʂ̒����ɐݒ肳���)
	SetCursorPos(basePt.x, basePt.y);
	D3DXMatrixIdentity(&billBoardMat);
	hasPosed = false;
	MakeSnowBallFlag = false;
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(StageBorder & StageBorder)
{
	if (MakeSnowBallFlag == true)
	{
		hasPosed = MakeSnowBallPose();

		D3DXMatrixRotationY(&rotMatY, D3DXToRadian(angY));				//�X������������]������

		D3DXMatrixRotationX(&rotMatX, D3DXToRadian(angX));				//�X������������]������
		rotMat = rotMatX * rotMatY;

		SetCursorPos(basePt.x, basePt.y);	//�J�[�\���ʒu���Z�b�g
		return;				//�ړ����_�ړ��͎��s���Ȃ�
	}
	else
	{
		hasPosed = false;
		if (pos.y <= CAM_HIGHT)
		{
			pos.y += SQUAT_SPEED;			//�����オ�鏈��
			if (pos.y >= CAM_HIGHT)
			{
				pos.y = CAM_HIGHT;			//�����ꍂ�������ꂽ�����C������
			}
		}
	}

	POINT Pt;
	ClientToScreen(hwnd, &Pt);		//�X�N���[�����W���W�ɕϊ�
	GetCursorPos(&Pt);					//���݂̃J�[�\���̈ʒu�������
	angY += ((Pt.x - basePt.x) / 4.0f) * mouseSensitivityX;	//�ŏ��̈ʒu�Ƃ̍������߁A�ړ��ʂ𒲐����Ă���

	angX += ((Pt.y - basePt.y) / 4.0f) * mouseSensitivityY;
	SetCursorPos(basePt.x, basePt.y);	//�J�[�\���ʒu���Z�b�g

	//------------------------------------------
	//�p�x����
	//------------------------------------------
	if (angX >= 70)
	{
		angX = 70;
	}

	if (angX <= -50)
	{
		angX = -50;
	}
	//------------------------------------------
	D3DXMatrixRotationY(&rotMatY, D3DXToRadian(angY));				//�X������������]������

	D3DXMatrixRotationX(&rotMatX, D3DXToRadian(angX));				//�X������������]������

	rotMat = rotMatX * rotMatY;

	Move(StageBorder);
}

void PlayerCamera::SetCamera(void)
{
	D3DXVECTOR3 camTmpVec, camHead;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &rotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��
	D3DXVec3TransformCoord(&camHead, &D3DXVECTOR3(0, 1, 0), &rotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��

	//���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y, pos.z),	// �J�����̈ʒu	
		&(D3DXVECTOR3(pos.x, pos.y, pos.z) + camTmpVec),	// �J�����̎��_
		&camHead	// �J�����̓��̕���
	);


	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 2000.0f);

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

D3DXMATRIX PlayerCamera::GetmView(void)
{
	return mView;
}

D3DXVECTOR3 PlayerCamera::GetmoveVec(void)
{
	return moveVec;
}

D3DXVECTOR3 PlayerCamera::GetPos(void)
{
	return pos;
}

bool PlayerCamera::GetHasPosed(void)
{
	return hasPosed;
}

void PlayerCamera::PushPos(D3DXVECTOR3 *PushVec)
{
	pos += *PushVec;
}

void PlayerCamera::SetPos(D3DXVECTOR3 * SetPos)
{
	pos = *SetPos;
	pos.y = CAM_HIGHT;
}

void PlayerCamera::SetMakeSnowBallFlag(bool Flag)
{
	MakeSnowBallFlag = Flag;
}

void PlayerCamera::SetMoveSpeed(float MoveSpeed)
{
	moveSpeed = MoveSpeed;
}

//=====================================
//private���\�b�h
//=====================================
void PlayerCamera::Move(StageBorder & StageBorder)
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
	if (pos.z > StageBorder.Top)
	{
		pos.z += StageBorder.Top - pos.z;
	}

	if (pos.z < StageBorder.Bottom)
	{
		pos.z += StageBorder.Bottom - pos.z;
	}

	if (pos.x < StageBorder.Left)
	{
		pos.x += StageBorder.Left - pos.x;
	}

	if (pos.x > StageBorder.Right)
	{
		pos.x += StageBorder.Right - pos.x;
	}

}

bool PlayerCamera::MakeSnowBallPose(void)
{
	if (pos.y > 3.0f)
	{
		pos.y -= SQUAT_SPEED;
	}

	if (angX < -20.0f)
	{
		angX += 3.0f;
		return false;
	}

	if (angX < MAKEBALL_CAM_ANG)
	{
		angX += 1.5f;
	}
	else
	{
		return true;
	}
	return false;
}
