#include "DecorationBase.h"

void DecorationBase::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool DecorationBase::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	D3DXVECTOR3 TargetVec;
	TargetVec = pos - *_Pos;		//2�_�̃x�N�g�������߂�

	float TargetLength;
	TargetLength = D3DXVec3Length(&TargetVec);	//2�_�̋��������߂�	

	if (TargetLength < picUpDistans)		//2�_�̋������E�����Ƃ��ł��鋗����菬����������
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
