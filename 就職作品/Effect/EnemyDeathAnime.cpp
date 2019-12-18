#include "EnemyDeathAnime.h"
EnemyDeathAnime::EnemyDeathAnime(D3DXMATRIX _Mat, XFILE _Mesh, D3DXVECTOR3 _Vec)
{
	//������

	mesh = _Mesh;
	startRotMat = _Mat;
	mat = _Mat;
	ang = 0;

	//��]�������߂�

	_Vec.y = 0;		//Y�����͖�������
	D3DXVec3Normalize(&_Vec, &_Vec);		//��ʂ̕����x�N�g���̋t�ɓ|���

	D3DXVec3Cross(&RotAxis, &D3DXVECTOR3(0, 1, 0), &_Vec);			//Y�����Ɛ�ʂ̐i�s�����ŊO�ς����߉�]���ɂ���

	D3DXMATRIX InvMat;
	InvMat = startRotMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//�t�s������

	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &InvMat);		//��]����Ώۂ̃��[�J�����W�ɕϊ�����
}

EnemyDeathAnime::~EnemyDeathAnime()
{
}

void EnemyDeathAnime::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool EnemyDeathAnime::Update(void)
{
	ang += 4.5f;
	D3DXMatrixRotationAxis(&rotMat, &RotAxis, D3DXToRadian(ang));		//�̂������������

	if (ang > 90.0f)		//�p�x��90�x�𒴂�����I��
	{
		return false;
	}

	mat = rotMat * startRotMat;

	return true;
}