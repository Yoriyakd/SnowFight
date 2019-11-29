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
	
	D3DXMATRIX tmpMat;
	moveVec.y += SnowBallGravity;		//�n�ʂɗ����Ă���

	D3DXMatrixTranslation(&tmpMat, moveVec.x, moveVec.y, moveVec.z);

	mat = tmpMat * mat;

	if (mat._42 <= 0.0f)		//�n�ʂɖ�����Ȃ�
	{
		mat._42 = 0.0f;

		//�n�ʂɂ��Ə��������Ď~�܂�
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
