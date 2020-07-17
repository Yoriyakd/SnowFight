#include "EnemyDeathAnime.h"
#include"../DirectX/Direct3D.h"
EnemyDeathAnime::EnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall)
{
	//������

	mesh = GetResource.GetXFILE(EnemyBody_M);
	mat = startMat = Enemy.GetMat();

	nowAng = 0;

	//��]�������߂�
	D3DXVECTOR3 SnowBallVecTmp;

	SnowBallVecTmp = SnowBall.GetMoveVec();

	SnowBallVecTmp.y = 0;		//Y�����͖�������
	D3DXVec3Normalize(&SnowBallVecTmp, &SnowBallVecTmp);		//��ʂ̕����x�N�g���̋t�ɓ|���

	D3DXVec3Cross(&rotAxis, &D3DXVECTOR3(0, 1, 0), &SnowBallVecTmp);			//Y�����Ɛ�ʂ̐i�s�����ŊO�ς����߉�]���ɂ���

	D3DXMATRIX InvMat;
	InvMat = startMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//�t�s������

	D3DXVec3TransformNormal(&rotAxis, &rotAxis, &InvMat);		//��]����Ώۂ̃��[�J�����W�ɕϊ�����
}

EnemyDeathAnime::~EnemyDeathAnime()
{
}

void EnemyDeathAnime::Draw(void)
{
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool EnemyDeathAnime::Update(void)
{
	nowAng += 4.5f;
	D3DXMatrixRotationAxis(&rotMat, &rotAxis, D3DXToRadian(nowAng));		//�̂������������

	if (nowAng > 90.0f)		//�p�x��90�x�𒴂�����I��
	{
		return false;
	}

	mat = rotMat * startMat;		//�ŏ��̎p���ɉ�]�s��𑫂��Ă���

	return true;
}