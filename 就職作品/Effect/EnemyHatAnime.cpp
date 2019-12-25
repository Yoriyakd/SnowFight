#include "EnemyHatAnime.h"

EnemyHatAnime::EnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot)
{
	//‰Šú‰»

	mesh = GetResource.GetXFILE("EnemyHat.x");
	mat = startRotMat = Enemy.GetHatMat();

	//‰ñ“]²‚ğ‹‚ß‚é
	D3DXVECTOR3 SnowBallMoveVec;

	SnowBallMoveVec = SnowBall.GetMoveVec();

	SnowBallMoveVec.y = 0;		//Y•ûŒü‚Í–³‹‚·‚é
	D3DXVec3Normalize(&SnowBallMoveVec, &SnowBallMoveVec);		//á‹Ê‚Ì•ûŒüƒxƒNƒgƒ‹‚Ì‹t‚É“|‚ê‚é

	D3DXVec3Cross(&rotAxis, &D3DXVECTOR3(0, 1, 0), &SnowBallMoveVec);			//Y•ûŒü‚Æá‹Ê‚Ìis•ûŒü‚ÅŠOÏ‚ğ‹‚ß‰ñ“]²‚É‚·‚é

	D3DXMATRIX InvMat;
	InvMat = startRotMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//‹ts—ñ‚ğì‚é

	D3DXVec3TransformNormal(&rotAxis, &rotAxis, &InvMat);		//‰ñ“]²‚ğ‘ÎÛ‚Ìƒ[ƒJƒ‹À•W‚É•ÏŠ·‚·‚é

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

	
	//mat = rotMat * startRotMat;		//Å‰‚Ìp¨‚É‰ñ“]s—ñ‚ğ‘«‚µ‚Ä‚¢‚­
	mat = rotMat * mat;		//‰ñ“]s—ñ‚ğ‘«‚µ‚Ä‰ñ“]‚³‚¹‚Ä‚¢‚­

	

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