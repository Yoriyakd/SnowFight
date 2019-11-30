#include "CollisionObserver.h"

CollisionObserver::CollisionObserver()
{
}

CollisionObserver::~CollisionObserver()
{
}

bool CollisionObserver::SnowBalltoEnemy(SnowBall * SnowBall, Enemy * Enemy)		//�Ăяo������for�����񂷂悤�ɕύX����
{
	//---------------------------------------------------------------
	//�K�v�Ȓl��p��
	CollisionSphere SnowBallSphre, EnemySphreA, EnemySphreB;//A����B����

	Enemy->GetCollisionSphere(&EnemySphreA, &EnemySphreB);		/*�����蔻��̋��̃f�[�^�擾*/
	SnowBall->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
	//---------------------------------------------------------------

	if (CollisionDetection(&SnowBallSphre, &EnemySphreA) || CollisionDetection(&SnowBallSphre, &EnemySphreB))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionObserver::SnowBalltoObj(SnowBall * SnowBall, MapObj * MapObj)
{
	//�K�v�Ȓl��p��

	XFILE MeshTmp;
	D3DXMATRIX MeshMat;
	D3DXVECTOR3 RayVec, RayPos;
	float MeshDis;

	MeshTmp = MapObj->GetMesh();
	MeshMat = MapObj->GetMat();
	RayPos = SnowBall->GetPos();
	RayVec = SnowBall->GetMoveVec();
	D3DXVec3Normalize(&RayVec, &RayVec);

	if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//���b�V���ɑ΂��ă��C����
	{
		CollisionSphere SnowBallSphere;
		SnowBall->GetCollisionSphere(&SnowBallSphere);

		if (MeshDis < SnowBallSphere.radius)										//���������a�ȉ��Ȃ�
		{
			
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void CollisionObserver::PlayertoObj(PlayerCamera * PlayerCam, MapObj * MapObj)
{
	D3DXVECTOR3 PlayerPosTmp, PlayerMoveVecTmp;
	PlayerPosTmp = PlayerCam->GetPos();
	PlayerPosTmp.y = 0;				//Y���W�����̈ʒu�Ȃ̂ŕύX
	PlayerMoveVecTmp = PlayerCam->GetmoveVec();

	CollisionDetectionType TypeTmp;
	TypeTmp = MapObj->GetCollisionDetectionType();

	if (TypeTmp == Ray)
	{
		D3DXMATRIX ObjMatTmp;
		ObjMatTmp = MapObj->GetMat();
		D3DXMATRIX invMat;

		D3DXMatrixInverse(&invMat, NULL, &ObjMatTmp);

		D3DXVECTOR3 LocalPos, LocalVec;

		D3DXVec3TransformCoord(&LocalPos, &PlayerPosTmp, &invMat);		//���ꂼ��̋t�s������
		D3DXVec3TransformNormal(&LocalVec, &PlayerMoveVecTmp, &invMat);
		D3DXVec3Normalize(&LocalVec, &LocalVec);


		BOOL hit; float meshDis; DWORD PolyNo; XFILE ObjMesh;

		ObjMesh = MapObj->GetMesh();

		D3DXIntersect(ObjMesh.lpMesh, &LocalPos, &LocalVec, &hit, &PolyNo, NULL, NULL, &meshDis, NULL, NULL);
		if (hit == TRUE)
		{
			WORD *pI;
			ObjMesh.lpMesh->LockIndexBuffer(0, (LPVOID*)&pI);
			DWORD vertexNo[3];
			vertexNo[0] = *(pI + PolyNo * 3 + 0);		//PolyNo�Ԗڂ̍\������1�߂̃C���f�b�N�X
			vertexNo[1] = *(pI + PolyNo * 3 + 1);
			vertexNo[2] = *(pI + PolyNo * 3 + 2);

			CLONEVERTEX *pV;

			ObjMesh.lpMesh->LockVertexBuffer(0, (LPVOID*)&pV);

			D3DXVECTOR3 vPos[3];

			vPos[0] = (pV + vertexNo[0])->Pos;			//��Ŏ�ɓ��ꂽ�C���f�b�N�X��p���Ă��̒��_�̍��W�𓾂�
			vPos[1] = (pV + vertexNo[1])->Pos;
			vPos[2] = (pV + vertexNo[2])->Pos;

			ObjMesh.lpMesh->UnlockVertexBuffer();

			D3DXVECTOR3 Vec1, Vec2;

			Vec1 = vPos[1] - vPos[0];			//2�ӗp��
			Vec2 = vPos[2] - vPos[0];

			D3DXVECTOR3 ObjNormal;

			D3DXVec3Cross(&ObjNormal, &Vec1, &Vec2);	//�|���S����2�ӂ̊O�ς����ߖ@�������߂�
			D3DXVec3TransformNormal(&ObjNormal, &ObjNormal, &ObjMatTmp);		//�\���Ɏg���s����g���ăO���[�o�����W�������߂Ă���
			D3DXVec3Normalize(&ObjNormal, &ObjNormal);	//���K��

			float Dot;
			Dot = D3DXVec3Dot(&ObjNormal, &-PlayerMoveVecTmp);		//���ς����߂�	��������1�Ȃ̂ŃR�T�C���ƂɂȂ�
			float Limit;					//�O�p�`�̎Εӂ̒���
			Limit = 3 / Dot;				//3�͕ǂ��痣����������
			if (Limit < 0)Limit *= -1;		//�t����ǂɐڋ߂����ꍇ-�ɂȂ�̂Ŕ��]

			if (meshDis < Limit)
			{
				D3DXVECTOR3 PushVec;
				PushVec = ObjNormal * ((Limit - meshDis) * Dot);	//�@�������ɉ����o��
				PushVec.y = 0;									//�΂߂̕ǂɂԂ���ƒn�ʂɖ��܂�̂�y�����̈ړ���0�ɂ��Ă���
				PlayerCam->PushPos(&PushVec);
			}
		}
	}
	else
	{
		if (TypeTmp == Circles)
		{
			D3DXVECTOR3 TargetVec, ObjPosTmp;
			ObjPosTmp = MapObj->GetPos();

			TargetVec = D3DXVECTOR3(PlayerPosTmp.x, 0.0f, PlayerPosTmp.z) - ObjPosTmp;		//Y���W�𖳎�����

			float TargetLength;

			TargetLength = D3DXVec3Length(&TargetVec);

			const float PlayerRadius = 2.0f, ObjRadius = MapObj->GetRadius();

			if (TargetLength < PlayerRadius + ObjRadius)		//����
			{
				D3DXVec3Normalize(&TargetVec, &TargetVec);
				TargetVec *= (PlayerRadius + ObjRadius - TargetLength);
				D3DXMATRIX TmpMat;

				PlayerCam->PushPos(&TargetVec);
			}
		}
	}
}

bool CollisionObserver::EnemySnowBalltoPlayer(Player * Player, SnowBall * SnowBall)
{
	//---------------------------------------------------------------
	//�K�v�Ȓl��p��

	CollisionSphere SnowBallSphre, PlayerSphre;

	Player->GetCollisionSphere(&PlayerSphre);				/*�����蔻��̋��̃f�[�^�擾*/
	SnowBall->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
	//---------------------------------------------------------------

	if (CollisionDetection(&SnowBallSphre, &PlayerSphre))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CollisionObserver::DecorationToMapObj(DecorationBase * Decoration, MapObj * MapObj)
{
	//---------------------------------------------------------------
	//�K�v�Ȓl��p��

	XFILE MeshTmp;
	D3DXMATRIX MeshMat;
	D3DXVECTOR3 RayVec, RayPos;
	float MeshDis;

	MeshTmp = MapObj->GetMesh();
	MeshMat = MapObj->GetMat();
	RayPos = Decoration->GetPos();
	RayVec = Decoration->GetMoveVec();

	D3DXVec3Normalize(&RayVec, &RayVec);

	//---------------------------------------------------------------

	if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//���b�V���ɑ΂��ă��C����
	{
		float Radius = 3.0f;

		if (MeshDis < Radius)										//���������a�ȉ��Ȃ�
		{
		}
	}


}

