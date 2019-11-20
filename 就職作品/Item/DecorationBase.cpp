#include "DecorationBase.h"

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
	return false;
}

void DecorationBase::Updata()
{
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);
}

D3DXVECTOR3 DecorationBase::GetPos()
{
	return pos;
}

void DecorationBase::SetPos(D3DXVECTOR3 * _Pos)
{
	pos = *_Pos;
}

bool DecorationBase::GetPicUpFlag(void)
{
	return picUpFlag;
}

DecorationID DecorationBase::GetID(void)
{
	return decorationID;
}
