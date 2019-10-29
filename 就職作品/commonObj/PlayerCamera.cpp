#include "PlayerCamera.h"
//SCRW, SCRH, HWND
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
}

PlayerCamera::~PlayerCamera()
{
	ShowCursor(TRUE);			//�J�[�\����\������	��FTRUE�̉񐔂��J�E���g���Ă���̂ŕK�v�ȏ�ɌĂ΂Ȃ�
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

	D3DXVECTOR3 camTmpVec,camHead;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &rotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��
	D3DXVec3TransformCoord(&camHead, &D3DXVECTOR3(0, 1, 0), &rotMat);	//�ŏ��̌����ƌX�������̃x�N�g�������킹��


	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(pos.x, pos.y, pos.z),	// �J�����̈ʒu	
		&(D3DXVECTOR3(pos.x, pos.y, pos.z) + camTmpVec),	// �J�����̎��_
		&camHead	// �J�����̓��̕���
	);

	D3DXMatrixLookAtLH(&billBoardMat,
		&D3DXVECTOR3(0, 0, 0),	// �J�����̈ʒu	
		&camTmpVec,	// �J�����̎��_
		&camHead	// �J�����̓��̕���
	);

	D3DXMatrixInverse(&billBoardMat, NULL, &billBoardMat);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRw / (float)SCRh, 1.0f, 2000.0f);

	//�s��ݒ�
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void PlayerCamera::SetCamPos(D3DXVECTOR3* pPos)
{
	pos = *pPos;
	pos.y = camHight;
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


