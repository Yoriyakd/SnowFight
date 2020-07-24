#include "BackOriginalPose.h"
#include"../Enemy.h"
#include"EngagingMode.h"

BackOriginalPose::BackOriginalPose():nowAnimeFrame(0.0f)
{
	invRotMat = nullptr;
}

BackOriginalPose::~BackOriginalPose()
{
	delete invRotMat;
}

EnemyStateBase * BackOriginalPose::Action(Enemy &Enemy)
{
	if (nowAnimeFrame >= 1.0f)return new EngagingMode();
	MakeInvMat(Enemy.GetMat());

	nowAnimeFrame += ANIME_SPEED;
	if (nowAnimeFrame >= 1.0f)nowAnimeFrame = 1.0f;
	
	QuaternionAnime(&nowMat, &nowMat, &startMat, &endMat, nowAnimeFrame);


	D3DXMATRIX TmpMat;

	TmpMat = Enemy.GetMat();

	TmpMat._11 = nowMat._11;
	TmpMat._12 = nowMat._12;
	TmpMat._13 = nowMat._13;

	TmpMat._21 = nowMat._21;
	TmpMat._22 = nowMat._22;
	TmpMat._23 = nowMat._23;

	TmpMat._31 = nowMat._31;
	TmpMat._32 = nowMat._32;
	TmpMat._33 = nowMat._33;
	
	

	Enemy.SetMat(TmpMat);

	return nullptr;
}

void BackOriginalPose::MakeInvMat(const D3DXMATRIX &Mat)
{
	if (invRotMat != nullptr)return;
	invRotMat = new D3DXMATRIX;

	*invRotMat = Mat;

	//•½sˆÚ“®¬•ª‚ðÁ‚·
	invRotMat->_41 = 0.0f;
	invRotMat->_42 = 0.0f;
	invRotMat->_43 = 0.0f;
	
	startMat = *invRotMat;
	nowMat = *invRotMat;

	D3DXVECTOR3 TmpVec;

	TmpVec.x = invRotMat->_11;
	TmpVec.y = 0.0f;
	TmpVec.z = invRotMat->_13;

	D3DXVec3Normalize(&TmpVec, &TmpVec);
	//xŽ²
	invRotMat->_11 = TmpVec.x;
	invRotMat->_12 = TmpVec.y;
	invRotMat->_13 = TmpVec.z;

	//yŽ²
	invRotMat->_21 = 0.0f;
	invRotMat->_22 = 1.0f;
	invRotMat->_23 = 0.0f;

	//zŽ²
	TmpVec.x = invRotMat->_31;
	TmpVec.y = 0.0f;
	TmpVec.z = invRotMat->_33;

	D3DXVec3Normalize(&TmpVec, &TmpVec);

	invRotMat->_31 = TmpVec.x;
	invRotMat->_32 = TmpVec.y;
	invRotMat->_33 = TmpVec.z;

	endMat = *invRotMat;
}
