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
	else
	{
		picUpFlag = false;
	}

	return false;
}

void DecorationBase::Updata()
{
	static const float Gravity = -0.1f;
	pos.y += Gravity;
	if (pos.y <= 0)		//�n�ʂɖ�����Ȃ�
	{
		pos.y = 0;
	}
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
