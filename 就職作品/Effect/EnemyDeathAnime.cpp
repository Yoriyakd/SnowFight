#include "EnemyDeathAnime.h"
#include"../DirectX/Direct3D.h"
EnemyDeathAnime::EnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall)
{
	//初期化

	mesh = GetResource.GetXFILE(EnemyBody_M);
	mat = startMat = Enemy.GetMat();

	nowAng = 0;

	//回転軸を求める
	D3DXVECTOR3 SnowBallVecTmp;

	SnowBallVecTmp = SnowBall.GetMoveVec();

	SnowBallVecTmp.y = 0;		//Y方向は無視する
	D3DXVec3Normalize(&SnowBallVecTmp, &SnowBallVecTmp);		//雪玉の方向ベクトルの逆に倒れる

	D3DXVec3Cross(&rotAxis, &D3DXVECTOR3(0, 1, 0), &SnowBallVecTmp);			//Y方向と雪玉の進行方向で外積を求め回転軸にする

	D3DXMATRIX InvMat;
	InvMat = startMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//逆行列を作る

	D3DXVec3TransformNormal(&rotAxis, &rotAxis, &InvMat);		//回転軸を対象のローカル座標に変換する
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
	D3DXMatrixRotationAxis(&rotMat, &rotAxis, D3DXToRadian(nowAng));		//のけぞる方向が正

	if (nowAng > 90.0f)		//角度が90度を超えたら終了
	{
		return false;
	}

	mat = rotMat * startMat;		//最初の姿勢に回転行列を足していく

	return true;
}