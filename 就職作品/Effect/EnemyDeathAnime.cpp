#include "EnemyDeathAnime.h"
EnemyDeathAnime::EnemyDeathAnime(D3DXMATRIX _Mat, XFILE _Mesh, D3DXVECTOR3 _Vec)
{
	//初期化

	mesh = _Mesh;
	startRotMat = _Mat;
	mat = _Mat;
	ang = 0;

	//回転軸を求める

	_Vec.y = 0;		//Y方向は無視する
	D3DXVec3Normalize(&_Vec, &_Vec);		//雪玉の方向ベクトルの逆に倒れる

	D3DXVec3Cross(&RotAxis, &D3DXVECTOR3(0, 1, 0), &_Vec);			//Y方向と雪玉の進行方向で外積を求め回転軸にする

	D3DXMATRIX InvMat;
	InvMat = startRotMat;

	D3DXMatrixInverse(&InvMat, NULL, &InvMat);		//逆行列を作る

	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &InvMat);		//回転軸を対象のローカル座標に変換する
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
	D3DXMatrixRotationAxis(&rotMat, &RotAxis, D3DXToRadian(ang));		//のけぞる方向が正

	if (ang > 90.0f)		//角度が90度を超えたら終了
	{
		return false;
	}

	mat = rotMat * startRotMat;

	return true;
}