#include "EnemyHatAnime.h"
#include"../DirectX/Direct3D.h"

const D3DXVECTOR3 EnemyHatAnime::DEFAULT_HIT_FLYING_HIGHT = D3DXVECTOR3(0.0f, 0.8f, 0.0f);
const float EnemyHatAnime::HEAD_HIT_FLYING_HIGHT = 1.5f;
const float EnemyHatAnime::HAT_GRAVITY = -0.1f;
const int EnemyHatAnime::ROT_SPEED = 15;

EnemyHatAnime::EnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot)
{
	//初期化

	mesh = GetResource.GetXFILE(EnemyHat_M);
	mat = startRotMat = Enemy.GetHatMat();

	//回転軸を求める
	D3DXVECTOR3 SnowBallMoveVec;

	SnowBallMoveVec = SnowBall.GetMoveVec();

	SnowBallMoveVec.y = 0;		//Y方向は無視する
	D3DXVec3Normalize(&SnowBallMoveVec, &SnowBallMoveVec);		//雪玉の方向ベクトルの逆に倒れる

	D3DXVec3Cross(&rotAxis, &D3DXVECTOR3(0, 1, 0), &SnowBallMoveVec);			//Y方向と雪玉の進行方向で外積を求め回転軸にする

	D3DXMATRIX InvMat;
	InvMat = startRotMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//逆行列を作る

	D3DXVec3TransformNormal(&rotAxis, &rotAxis, &InvMat);		//回転軸を対象のローカル座標に変換する

	moveVec = DEFAULT_HIT_FLYING_HIGHT;

	if (HeadShot == true)
	{
		moveVec.y = HEAD_HIT_FLYING_HIGHT;
	}

	moveVec += SnowBall.GetMoveVec();

	
}

void EnemyHatAnime::Draw()
{
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool EnemyHatAnime::Update()
{
	D3DXMatrixRotationAxis(&rotMat, &rotAxis, D3DXToRadian(ROT_SPEED));

	mat = rotMat * mat;		//回転行列を足して回転させていく

	

	D3DXMATRIX TmpTransMat;

	moveVec.y += HAT_GRAVITY;

	D3DXMatrixTranslation(&TmpTransMat, moveVec.x, moveVec.y, moveVec.z);
	mat = mat * TmpTransMat;

	if (mat._42 < GROUND_HIGHT)
	{
		return false;
	}

	return true;
}