#include "Player.h"

extern ResourceManager *resourceManager;
//=====================================
//private���\�b�h
//=====================================

void Player::Move(void)
{
	///*--�����Ŗ��񃊃Z�b�g���Ă���--*/
	//bool moveFlag = false;
	//D3DXVECTOR3 moveVec(0, 0, 0);
	///*--�����Ŗ��񃊃Z�b�g���Ă���--*/
	//D3DXVECTOR3 TmpVec;


	//if (GetAsyncKeyState('W') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, 1), &camRotMatX);
	//	/*������؂�ւ��đ��̃L�[�����*/
	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(-1, 0, 0), &camRotMatX);

	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}
	//if (GetAsyncKeyState('S') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, -1), &camRotMatX);

	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}
	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(1, 0, 0), &camRotMatX);

	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}

	////�����Ă�Ԃ�������
	//if (moveFlag == true)
	//{
	//	D3DXVec3Normalize(&moveVec, &moveVec);

	//	D3DXMATRIX tmpMat;
	//	D3DXMatrixTranslation(&tmpMat,
	//		moveVec.x,
	//		moveVec.y,
	//		moveVec.z);

	//	D3DXVECTOR3 nowVec;
	//	D3DXVec3TransformNormal(&nowVec, &D3DXVECTOR3(0, 0, 1), &rotMat);			//�������Ă�������̃x�N�g�������Ă���		//�m��������1�ɂ��Ă���΂߈ړ��������Ȃ��̑΍�
	//	D3DXVec3Normalize(&moveVec, &moveVec);
	//	float tmpAng;
	//	tmpAng = D3DXVec3Dot(&nowVec, &moveVec);
	//	tmpAng = D3DXToDegree(acos(tmpAng));

	//	if (tmpAng >= 0.1f)			//float�^�ł�== ��!=�@���g��Ȃ�
	//	{
	//		D3DXVECTOR3 crossVec;
	//		D3DXVec3Cross(&crossVec, &nowVec, &moveVec);			//�O�ς��v�Z���ăx�N�g�����ォ����������

	//		if (tmpAng >= 10.0f)			//������肩���Ă񂳂��鏈��
	//		{
	//			tmpAng = 8.0f;
	//		}

	//		if (crossVec.y > 0.1f)			//�����̌����𑝂₷�ƐU�����Ȃ��Ȃ���ۂ�
	//		{
	//			camAngY += tmpAng;
	//		}
	//		else
	//		{
	//			if (crossVec.y < -0.1f)		//�����̌����𑝂₷�ƐU�����Ȃ��Ȃ���ۂ�
	//			{
	//				camAngY -= tmpAng;
	//			}
	//			else
	//			{
	//				camAngY += tmpAng;			//180�x�J���Ă���悤�ȂƂ���(�ǂ���ɂ����Ă͂܂�Ȃ�)
	//			}
	//		}
	//	}

	//	D3DXMatrixRotationY(&rotMat, D3DXToRadian(camAngY));

	//	transMat = tmpMat * transMat;
	//}

	//mat = rotMat * transMat;
}

int Player::ShootSnowball(void)
{
	return 0;
}

//=====================================
//public���\�b�h
//=====================================

Player::Player()
{
	mesh = resourceManager->GetXFILE("Player/player.x");
	SetCursorPos(SCRW / 2, SCRH / 2);
	camAngX = 0, camAngY = 0;
	basePt.x = SCRH / 2;
	basePt.y = SCRW / 2;

	ClientToScreen(hwnd, &basePt);
	SetCursorPos(basePt.x, basePt.y);
}

Player::~Player()
{

}

bool Player::Update(void)
{
	Move();
	D3DXMatrixTranslation(&mat, 0, 0, 0);		//��
	Pos.x = mat._41, Pos.y = mat._42 + 5, Pos.z = mat._43;		//Player�̍��W��Pos�ɓ����		�ꏊ�l����
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
	SetCursorPos(basePt.x, basePt.y);	//�J�[�\���ʒu���Z�b�g		�X�N���[�����W�ɕϊ������ق��������C������

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
		&Pos,	// �J�����̈ʒu
		&(Pos + camTmpVec),	// �J�����̎��_
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
}
