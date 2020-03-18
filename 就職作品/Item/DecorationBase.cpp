#include "DecorationBase.h"
#include"../GameScene/GameScene.h"

DecorationBase::DecorationBase() : canPicUp(false), isDecorated(false), decorationRadius(0.2)
{
}

DecorationBase::~DecorationBase()
{
}

void DecorationBase::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}

bool DecorationBase::CheckForCanPicUp(const D3DXVECTOR3 * _Pos)
{
	if (isDecorated == true)
	{
		return false;			//�����Ȃ���ԂȂ�E���Ȃ�
	}

	D3DXVECTOR3 TargetVec;
	TargetVec = pos - *_Pos;		//2�_�̃x�N�g�������߂�

	float TargetLength;
	TargetLength = D3DXVec3Length(&TargetVec);	//2�_�̋��������߂�	

	if (TargetLength < picUpDistans)		//2�_�̋������E�����Ƃ��ł��鋗����菬����������
	{
		canPicUp = true;
		return true;
	}
	else
	{
		canPicUp = false;
	}

	return false;
}

void DecorationBase::Updata()
{
	if (isDecorated == false)
	{
		Move();

		globalMoveVec = D3DXVECTOR3(mat._41, mat._42, mat._43) - memoryPos;				//���݂̍��W�ƋL�����Ă������O�t���[���̍��W���v�Z���ĉ�]�s����܂߂��ړ��x�N�g�������߂Ă���

		memoryPos = D3DXVECTOR3(mat._41, mat._42, mat._43);

		pos = D3DXVECTOR3(mat._41, mat._42, mat._43);
	}
	else
	{
		globalMoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (doDecoratFlag == true)
	{
		doDecoratFlag = false;
		Move();
		DecorateEffect();
	}
}


void DecorationBase::SetPos(D3DXVECTOR3 * _Pos)
{
	pos = *_Pos;
}

void DecorationBase::SetMoveVec(const D3DXVECTOR3 &_Vec)
{
	D3DXMATRIX InvMat;

	D3DXMatrixInverse(&InvMat, NULL, &mat);
	D3DXVec3TransformNormal(&moveVec,  &_Vec, &InvMat);
}

D3DXVECTOR3 DecorationBase::GetPos()
{
	return pos;
}


bool DecorationBase::GetPicUpFlag(void)
{
	return canPicUp;
}

CarryObjectID DecorationBase::GetID(void)
{
	return decorationID;
}

D3DXVECTOR3 DecorationBase::GetMoveVec()
{
	return globalMoveVec;
}

void DecorationBase::SetDecoratedState(bool State)
{
	isDecorated = State;
}

bool DecorationBase::GetDecoratedState(void)
{
	return isDecorated;
}

void DecorationBase::DoDecorate(const D3DXVECTOR3 &TreeVec)
{
	float MoveVecLen, TreeVecLen;

	MoveVecLen = D3DXVec3Length(&moveVec);
	TreeVecLen= D3DXVec3Length(&TreeVec);

	if (TreeVecLen < MoveVecLen)
	{
		D3DXVec3Normalize(&moveVec, &moveVec);
		moveVec *= TreeVecLen + decorationRadius;
		doDecoratFlag = true;
		isDecorated = true;
	}
}

void DecorationBase::PushPos(const D3DXVECTOR3 &PushVec)
{
	D3DXMATRIX TmpMat;

	D3DXMatrixTranslation(&TmpMat, PushVec.x, PushVec.y, PushVec.z);
	mat = mat * TmpMat;
}

void DecorationBase::Move()
{
	D3DXMATRIX TmpMat;
	moveVec.y += SnowBallGravity;		//�n�ʂɗ����Ă���

	D3DXMatrixTranslation(&TmpMat, moveVec.x, moveVec.y, moveVec.z);

	mat = TmpMat * mat;		//�s��X�V

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
}

void DecorationBase::DecorateEffect()
{
	GetSound.Play2D(XmasTreeHit_Sound);
	GameNorm.DoDecorate();
}
