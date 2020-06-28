#include "ShootSnowBall.h"
#include"EngagingMode.h"
#include"../Enemy.h"

const float ShootSnowBall::ANIME_SPEED = 0.05f;

ShootSnowBall::ShootSnowBall()
{
	//振りかぶりアニメーションの終わりの行列を作成（毎回初期化してるの非効率何か考えないと）
	D3DXMATRIX TmpMat;
	D3DXMatrixRotationZ(&TmpMat, D3DXToRadian(45));		//傾く軸の角度

	D3DXVECTOR3 RotAxis(0, 1, 0);
	D3DXVec3TransformNormal(&RotAxis, &RotAxis, &TmpMat);
	D3DXMatrixRotationAxis(&windUpEndMat ,&RotAxis, D3DXToRadian(5));		//振りかぶり角度

	D3DXMatrixRotationAxis(&throwEndMat ,&RotAxis, D3DXToRadian(-5));		//ふり抜き角度

	D3DXMatrixIdentity(&windUpStartMat);
	D3DXMatrixIdentity(&throwStartMat);
	windUpAnimeFrame = 0;
	throwAnimeFrame = 0;
}


EnemyStateBase* ShootSnowBall::Action(Enemy& Enemy)
{
	if (Enemy.IsJump() == false)		//ジャンプ中は撃たない
	{
		//振りかぶり
		if (!WindUpAnime(Enemy))return nullptr;		//終了まで行う
		if (!ThrowAnime(Enemy))return nullptr;
		Enemy.ShootSnowBall();
		
		return new EngagingMode();
	}
	return nullptr;
}

bool ShootSnowBall::WindUpAnime(Enemy& Enemy)
{
	if (windUpAnimeFrame >= 1)
	{
		windUpAnimeFrame = 1;
		return true;		//動きが終了するとtrueを返す
	}

	QuaternionAnime(&nowMat, &nowMat, &windUpStartMat, &windUpEndMat, windUpAnimeFrame);
	windUpAnimeFrame += ANIME_SPEED;
	

	D3DXMATRIX TmpMat;

	TmpMat = Enemy.GetMat();

	TmpMat = nowMat * TmpMat;

	Enemy.SetMat(TmpMat);


	return false;
}

bool ShootSnowBall::ThrowAnime(Enemy& Enemy)
{
	if (throwAnimeFrame >= 1)
	{
		throwAnimeFrame = 1;
		return true;		//動きが終了するとtrueを返す
	}

	//ここで雪だるまが傾く動作追加
	QuaternionAnime(&nowMat, &nowMat, &throwStartMat, &throwEndMat, throwAnimeFrame);
	throwAnimeFrame += ANIME_SPEED;


	D3DXMATRIX TmpMat;

	TmpMat = Enemy.GetMat();

	TmpMat = nowMat * TmpMat;

	Enemy.SetMat(TmpMat);
	return false;
}

