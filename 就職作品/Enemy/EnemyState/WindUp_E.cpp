#include "WindUp_E.h"
#include"../Enemy.h"
#include"Throw_E.h"

WindUp_E::WindUp_E() : nowRotAng(0.0f)
{
}

EnemyStateBase * WindUp_E::Action(Enemy & Enemy)
{
	if (Enemy.IsJump() == true)return nullptr;
	if (nowRotAng >= END_ROT)
	{
		Enemy.SetShootFlag(true);		//�łO�Ɏ�Ɏ��`���[�W����
		return new Throw_E();		//�������I������Ǝ���state��Ԃ�
	}

	nowRotAng += ROT_SPEED;

	D3DXMATRIX TmpMat;
	D3DXMatrixRotationZ(&TmpMat, D3DXToRadian(45));		//�X�����̊p�x

	D3DXVECTOR3 RotAxis(0, 1, 0);
	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &TmpMat);
	D3DXMatrixRotationAxis(&TmpMat, &RotAxis, D3DXToRadian(ROT_SPEED));		//�U�肩�Ԃ�p�x

	TmpMat = TmpMat * Enemy.GetMat();

	Enemy.SetMat(TmpMat);

	return false;
}
