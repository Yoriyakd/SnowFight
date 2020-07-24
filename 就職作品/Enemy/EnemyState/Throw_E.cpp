#include "Throw_E.h"
#include"EngagingMode.h"
#include"BackOriginalPose.h"
#include"../Enemy.h"

Throw_E::Throw_E() : nowRotAng(0.0f)
{
}


EnemyStateBase* Throw_E::Action(Enemy& Enemy)
{
	if (nowRotAng <= END_ROT)
	{
		return new BackOriginalPose();		//“®‚«‚ªI—¹‚·‚é‚ÆŽŸ‚Ìstate‚ð•Ô‚·
	}

	nowRotAng += ROT_SPEED;


	D3DXMATRIX TmpMat;
	D3DXMatrixRotationZ(&TmpMat, D3DXToRadian(45));		//ŒX‚­Ž²‚ÌŠp“x

	D3DXVECTOR3 RotAxis(0, 1, 0);
	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &TmpMat);
	D3DXMatrixRotationAxis(&TmpMat, &RotAxis, D3DXToRadian(ROT_SPEED));		//U‚è‚©‚Ô‚èŠp“x

	TmpMat = TmpMat * Enemy.GetMat();

	Enemy.SetMat(TmpMat);
	
	return nullptr;
}