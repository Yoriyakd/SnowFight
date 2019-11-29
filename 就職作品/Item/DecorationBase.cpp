#include "DecorationBase.h"
#include"../GameScene/GameScene.h"

void DecorationBase::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool DecorationBase::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	D3DXVECTOR3 TargetVec;
	TargetVec = pos - *_Pos;		//2点のベクトルを求める

	float TargetLength;
	TargetLength = D3DXVec3Length(&TargetVec);	//2点の距離を求める	

	if (TargetLength < picUpDistans)		//2点の距離が拾うことができる距離より小さかったら
	{
		picUpFlag = true;
		return true;
	}
	else
	{
		picUpFlag = false;
	}

	return false;
}

void DecorationBase::Updata()
{
	
	D3DXMATRIX tmpMat;
	moveVec.y += SnowBallGravity;		//地面に落ちていく

	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);

	mat = tmpMat * mat;

	if (mat._42 <= 0.0f)		//地面に埋もれない
	{
		mat._42 = 0.0f;

		//地面につくと少し滑って止まる
		moveVec += D3DXVECTOR3(-0.1f, 0.0f, -0.1f);

		if (moveVec.x <= 0.0f)
		{
			moveVec.x = 0.0f;
		}

		if (moveVec.z <= 0.0f)
		{
			moveVec.z = 0.0f;
		}
	}

	globalMoveVec = D3DXVECTOR3(mat._41, mat._42, mat._43) - memoryPos;

	memoryPos = D3DXVECTOR3(mat._41, mat._42, mat._43);

	pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
}


void DecorationBase::SetPos(D3DXVECTOR3 * _Pos)
{
	pos = *_Pos;
}

D3DXVECTOR3 DecorationBase::GetPos()
{
	return pos;
}


bool DecorationBase::GetPicUpFlag(void)
{
	return picUpFlag;
}

DecorationID DecorationBase::GetID(void)
{
	return decorationID;
}

D3DXVECTOR3 DecorationBase::GetMoveVec()
{
	return globalMoveVec;
}
