#include"../main.h"
#include"../DirectX/Direct3D.h"
//-------------------------------------------------------
//�v���g�^�C�v�錾��main.h�ŋL�q
//-------------------------------------------------------

void DrawMesh(XFILE *XFile)
{
	for (DWORD i = 0; i < XFile->NumMaterial; i++)
	{
		Direct3D::GetInstance().GetD3DDevice()->SetMaterial(&(XFile->Mat[i]));
		Direct3D::GetInstance().GetD3DDevice()->SetTexture(0, XFile->Tex[i]);
		XFile->lpMesh->DrawSubset(i);
	}
}

//���W�A���a�A���W�A���a
//�߂�l�@HIT == true �������ĂȂ������� == falsle
bool SphereCollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB)
{
	float targetLengh;
	targetLengh = D3DXVec3Length(&(dataA->pos - dataB->pos));
	if (targetLengh <= dataA->radius + dataB->radius)
	{
		return true;
	}
	return false;
}


bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis, DWORD *PolyNo)
{
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &*MeshMat);

	D3DXVECTOR3 LocalPos, LocalVec;

	D3DXVec3TransformCoord(&LocalPos, &*LayPos, &InvMat);		//���C���ˈʒu
	D3DXVec3TransformNormal(&LocalVec, &*LayVec, &InvMat);			//���C���˕���

	BOOL Hit;

	if (MeshDis == nullptr)
	{
		MeshDis = NULL;
	}

	if (PolyNo == nullptr)
	{
		PolyNo = NULL;
	}

	D3DXIntersect(Mesh->lpMesh, &LocalPos, &LocalVec, &Hit, PolyNo, NULL, NULL, &*MeshDis, NULL, NULL);
	if (Hit == FALSE)
	{
		if (MeshDis != nullptr)		//�l�����������Ă���ꍇHIT���Ă��Ȃ����Ƃ�\��-1������
		{
			*MeshDis = -1;
		}
		return false;
	}
	return true;
}

D3DXVECTOR3 ThrowingInit(const ThrowingInitValue* ThrowingInitValue, D3DXMATRIX *Mat)
{
	float Power;
	D3DXVECTOR3 moveVec;
	Power = ((ThrowingInitValue->powerRate / 100)) * 3;		//�򋗗������̂��߂�3

	D3DXMatrixTranslation(Mat, ThrowingInitValue->shootPos.x, ThrowingInitValue->shootPos.y, ThrowingInitValue->shootPos.z);			//���ˈʒu

	moveVec = D3DXVECTOR3(0, (float)(Power * tan(D3DXToRadian(ThrowingInitValue->XAxisAng))), (float)(Power * cos(D3DXToRadian(ThrowingInitValue->XAxisAng))));	//���˂̃x�N�g�������߂�

	return moveVec;
}

void QuaternionAnime(D3DXMATRIX *OutMat, const D3DXMATRIX *NowMat, const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float AnimeFrame)
{
	D3DXQUATERNION StartQua, NowQua, EndQua;

	//�s����N�I�[�^�j�I���ɕϊ�

	D3DXQuaternionRotationMatrix(&NowQua, NowMat);
	D3DXQuaternionRotationMatrix(&StartQua, StartMat);
	D3DXQuaternionRotationMatrix(&EndQua, EndMat);

	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, AnimeFrame);

	D3DXMatrixRotationQuaternion(OutMat, &NowQua);

	D3DXVECTOR3 StartPos, NowPos, EndPos;
	//�J�n�n�_�ƏI���n�_�̍��W���Z�b�g
	StartPos = D3DXVECTOR3(StartMat->_41, StartMat->_42, StartMat->_43);
	EndPos = D3DXVECTOR3(EndMat->_41, EndMat->_42, EndMat->_43);

	//Lerp�ō��W���ړ�
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, AnimeFrame);

	OutMat->_41 = NowPos.x;
	OutMat->_42 = NowPos.y;
	OutMat->_43 = NowPos.z;
}

void MakeBillBoardMat(D3DXMATRIX *OutMat, const D3DXMATRIX *_mView)
{
	D3DXMATRIX TmpMview;
	TmpMview = *_mView;

	TmpMview._41 = 0;			//�ړ��������폜
	TmpMview._42 = 0;
	TmpMview._43 = 0;

	D3DXMatrixInverse(OutMat, NULL, &TmpMview);		//�r���{�[�h�p���_�s��
}

bool IsOverProbabilityValue(const int &Probability)
{
	const int Percentage = 100;
	if (rand() % Percentage < Probability)
	{
		return true;
	}
	else
	{
		return false;
	}
}