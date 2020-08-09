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
		Enemy.SetShootFlag(true);		//打つ前に手に持つチャージする
		return new Throw_E();		//動きが終了すると次のstateを返す
	}

	nowRotAng += ROT_SPEED;

	D3DXMATRIX TmpMat;
	D3DXMatrixRotationZ(&TmpMat, D3DXToRadian(45));		//傾く軸の角度

	D3DXVECTOR3 RotAxis(0, 1, 0);
	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &TmpMat);
	D3DXMatrixRotationAxis(&TmpMat, &RotAxis, D3DXToRadian(ROT_SPEED));		//振りかぶり角度

	TmpMat = TmpMat * Enemy.GetMat();

	Enemy.SetMat(TmpMat);

	return false;
}
