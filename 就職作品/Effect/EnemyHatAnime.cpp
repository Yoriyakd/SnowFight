#include "EnemyHatAnime.h"

EnemyHatAnime::EnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot)
{
	//������

	mesh = GetResource.GetXFILE("EnemyHat.x");
	mat = startRotMat = Enemy.GetHatMat();

	//��]�������߂�
	D3DXVECTOR3 SnowBallMoveVec;

	SnowBallMoveVec = SnowBall.GetMoveVec();

	SnowBallMoveVec.y = 0;		//Y�����͖�������
	D3DXVec3Normalize(&SnowBallMoveVec, &SnowBallMoveVec);		//��ʂ̕����x�N�g���̋t�ɓ|���

	D3DXVec3Cross(&rotAxis, &D3DXVECTOR3(0, 1, 0), &SnowBallMoveVec);			//Y�����Ɛ�ʂ̐i�s�����ŊO�ς����߉�]���ɂ���

	D3DXMATRIX InvMat;
	InvMat = startRotMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//�t�s������

	D3DXVec3TransformNormal(&rotAxis, &rotAxis, &InvMat);		//��]����Ώۂ̃��[�J�����W�ɕϊ�����

	moveVec = D3DXVECTOR3(0.0f, 0.8f, 0.0f);

	if (HeadShot == true)
	{
		moveVec.y = 1.5f;
	}

	moveVec += SnowBall.GetMoveVec();

	
}

void EnemyHatAnime::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool EnemyHatAnime::Update()
{
	D3DXMatrixRotationAxis(&rotMat, &rotAxis, D3DXToRadian(15));

	
	//mat = rotMat * startRotMat;		//�ŏ��̎p���ɉ�]�s��𑫂��Ă���
	mat = rotMat * mat;		//��]�s��𑫂��ĉ�]�����Ă���

	

	D3DXMATRIX TmpTransMat;

	moveVec.y -= 0.1f;

	D3DXMatrixTranslation(&TmpTransMat, moveVec.x, moveVec.y, moveVec.z);
	mat = mat * TmpTransMat;

	if (mat._42 < 0.0f)
	{
		return false;
	}

	return true;
}