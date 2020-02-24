#include "CollisionObserver.h"

CollisionObserver::CollisionObserver()
{
}

CollisionObserver::~CollisionObserver()
{
}

bool CollisionObserver::SnowBalltoEnemyHat(SnowBall *SnowBall, Enemy *Enemy)
{
	if (SnowBall->GetID() == ENEMY_ID)return false;		//ID���G�̂��̂Ȃ瑁�����^�[��

	float HatRadius, HatHight, SnowBallRadius;
	D3DXVECTOR3 SnowBallPos;
	D3DXMATRIX HatMat;

	HatRadius = Enemy->GetHatRadius();
	HatHight = Enemy->GetHatHight();
	HatMat = Enemy->GetHatMat();

	SnowBallPos = SnowBall->GetPos();
	SnowBallRadius = SnowBall->GetSphereRadius();

	//�����~�����m�̔���
	D3DXVECTOR3 TargetVec;
	TargetVec = D3DXVECTOR3(HatMat._41, 0.0f, HatMat._43) - D3DXVECTOR3(SnowBallPos.x, 0.0f, SnowBallPos.z);		//Y���W�𖳎�����

	float TargetLength;

	TargetLength = D3DXVec3Length(&TargetVec);

	if (HatRadius + SnowBallRadius > TargetLength)		//���������a���m�𑫂������̂�菬�����Ȃ�A�����̔�����s��
	{
		D3DXVECTOR3 HightVec;
		HightVec = D3DXVECTOR3(0.0f, HatMat._42, 0.0f) - D3DXVECTOR3(0.0f, SnowBallPos.y, 0.0f);

		float HightLength;

		HightLength = D3DXVec3Length(&HightVec);

		if (HatHight / 2.0f + SnowBallRadius > HightLength)
		{
			return true;
		}
	}
	
	return false;
}



bool CollisionObserver::SnowBalltoEnemy(SnowBall *SnowBall, Enemy *Enemy)		//�Ăяo������for�����񂷂悤�ɕύX����
{
	if (SnowBall->GetID() == ENEMY_ID)return false;		//ID���G�̂��̂Ȃ瑁�����^�[��
	//---------------------------------------------------------------
	//�K�v�Ȓl��p��
	CollisionSphere SnowBallSphre, EnemySphreHead, EnemySphreBody;//A����B����

	Enemy->GetCollisionSphere(&EnemySphreHead, &EnemySphreBody);		/*�����蔻��̋��̃f�[�^�擾*/
	SnowBall->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
	//---------------------------------------------------------------

	if (SphereCollisionDetection(&SnowBallSphre, &EnemySphreHead) || SphereCollisionDetection(&SnowBallSphre, &EnemySphreBody))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionObserver::SnowBalltoObj(SnowBall *SnowBall, MapObj *MapObj)
{
	//�K�v�Ȓl��p��

	XFILE MeshTmp;
	D3DXMATRIX MeshMat;
	D3DXVECTOR3 LayVec, LayPos; D3DXVECTOR3 LayPosTmp;
	float MeshDis;

	MeshTmp = MapObj->GetMesh();
	MeshMat = MapObj->GetMat();
	LayPos = SnowBall->GetPos();
	LayVec = SnowBall->GetMoveVec();
	D3DXVec3Normalize(&LayVec, &LayVec);


	if (MeshCollisionDetection(&MeshTmp, &MeshMat, &LayPos, &LayVec, &MeshDis, nullptr))			//���b�V���ɑ΂��ă��C����
	{
		CollisionSphere SnowBallSphere;
		SnowBall->GetCollisionSphere(&SnowBallSphere);

		if (MeshDis < SnowBallSphere.radius + 2.0f)										//���������a�ȉ��Ȃ�	(�������傫�߂ɂƂ�)
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

void CollisionObserver::PlayertoObj(PlayerCamera *PlayerCam, MapObj *MapObj)
{
	D3DXVECTOR3 LayPos, LayVec;
	LayPos = PlayerCam->GetPos();
	LayPos.y = 0;						//Y���W�����̈ʒu�Ȃ̂ŕύX
	LayVec = PlayerCam->GetmoveVec();
	
	D3DXVec3Normalize(&LayVec, &LayVec);

	CollisionDetectionType TypeTmp;
	TypeTmp = MapObj->GetCollisionDetectionType();

	if (TypeTmp == Ray)
	{
		D3DXMATRIX ObjMatTmp;
		ObjMatTmp = MapObj->GetMat();

		float MeshDis; DWORD PolyNo; XFILE ObjMesh;

		ObjMesh = MapObj->GetMesh();

		if(MeshCollisionDetection(&ObjMesh, &ObjMatTmp, &LayPos, &LayVec, &MeshDis, &PolyNo) == true)
		{
			D3DXVECTOR3 ObjNormal;

			GetPolyNormal(&ObjNormal, ObjMesh.lpMesh, &PolyNo);

			D3DXVec3TransformNormal(&ObjNormal, &ObjNormal, &ObjMatTmp);		//�\���Ɏg���s����g���ă|���S�����̂̉�]���l�������x�N�g�������߂Ă���			���Y��Ȃ�

			float Dot;
			Dot = D3DXVec3Dot(&ObjNormal, &-LayVec);		//���ς����߂�	��������1�Ȃ̂ŃR�T�C���ƂɂȂ�		�@���̌����ɍ��킹�邽�߃x�N�g���𔽓]�����Ă���

			float Limit;					//�O�p�`�̎Εӂ̒���
			Limit = 3 / Dot;				//3�͕ǂ��痣����������

			if (Limit < 0)Limit *= -1;		//�t����ǂɐڋ߂����ꍇ-�ɂȂ�̂Ŕ��]

			if (MeshDis < Limit)
			{
				D3DXVECTOR3 PushVec;
				PushVec = ObjNormal * ((Limit - MeshDis) * Dot);	//�@�������ɉ����o�����������߂�
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

			TargetVec = D3DXVECTOR3(LayPos.x, 0.0f, LayPos.z) - ObjPosTmp;		//Y���W�𖳎�����

			float TargetLength;

			TargetLength = D3DXVec3Length(&TargetVec);

			const float PlayerRadius = 2.0f, ObjRadius = MapObj->GetRadius();

			if (TargetLength < PlayerRadius + ObjRadius)		//�����v���C���[���a��
			{
				D3DXVec3Normalize(&TargetVec, &TargetVec);
				TargetVec *= (PlayerRadius + ObjRadius - TargetLength);
				D3DXMATRIX TmpMat;

				PlayerCam->PushPos(&TargetVec);
			}
		}
	}
}

bool CollisionObserver::EnemySnowBalltoPlayer(Player *Player, SnowBall *SnowBall)
{
	if (SnowBall->GetID() == PLAYER_ID)return false;			//ID���v���C���[�̂��̂Ȃ瑁�����^�[��
	//---------------------------------------------------------------
	//�K�v�Ȓl��p��

	CollisionSphere SnowBallSphre, PlayerSphre;

	Player->GetCollisionSphere(&PlayerSphre);				/*�����蔻��̋��̃f�[�^�擾*/
	SnowBall->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
	//---------------------------------------------------------------
	SnowBallSphre.radius += 3.0f;

	if (SphereCollisionDetection(&SnowBallSphre, &PlayerSphre))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CollisionObserver::DecorationToMapObj(DecorationBase *Decoration, MapObj *MapObj, GameNormManager *GameNormManager)
{
	if (Decoration->GetDecoratedState() == true)return;		//��Ԃ������Ă���Ȃ�return�Ŕ�����
	//---------------------------------------------------------------
	//�K�v�Ȓl��p��

	XFILE ObjMesh;
	D3DXMATRIX ObjMat;
	D3DXVECTOR3 LayVec, LayPos, MoveVec;
	float MeshDis;

	ObjMesh = MapObj->GetMesh();
	ObjMat = MapObj->GetMat();
	LayPos = Decoration->GetPos();
	MoveVec = LayVec = Decoration->GetMoveVec();

	D3DXVec3Normalize(&LayVec, &LayVec);

	DWORD PolyNo;

	if (MeshCollisionDetection(&ObjMesh, &ObjMat, &LayPos, &LayVec, &MeshDis, &PolyNo))			//���b�V���ɑ΂��ă��C����
	{
		float Limit = 3.0f;

		D3DXVECTOR3 ObjNormal;

		GetPolyNormal(&ObjNormal, ObjMesh.lpMesh, &PolyNo);

		D3DXVec3TransformNormal(&ObjNormal, &ObjNormal, &ObjMat);		//�\���Ɏg���s����g���ă|���S�����̂̉�]���l�������x�N�g�������߂Ă���			���Y��Ȃ�

		float Dot;
		Dot = D3DXVec3Dot(&ObjNormal, &-LayVec);		//���ς����߂�	�i�s�x�N�g���ƕǂ̖@�� ��������1�Ȃ̂ŃR�T�C���ƂɂȂ�

		Limit = 4.5f / Dot;				//��������������Dot�Ŋ����ĎΕӂ̒��������߂Ă���

		if (Limit < 0)Limit *= -1;		//�t����ǂɐڋ߂����ꍇ-�ɂȂ�̂Ŕ��]

		if (MeshDis < Limit)										//���������a�ȉ��Ȃ�
		{
			if (MapObj->GetPossibleDecorate() == true)			//���邱�Ƃ��ł���Ȃ�
			{
				Decoration->SetDecoratedState(true);		//�����Ă����Ԃɂ���
				D3DXVECTOR3 PushVec;

				PushVec = LayVec * MeshDis;	//���b�V���܂ł̒������ړ�������
				Decoration->PushPos(&PushVec);
				GameNormManager->DoDecorate(Decoration->GetID());
				//GameNormManager->AddScore(500);
			}
			else
			{
				D3DXVECTOR3 PushVec;

				PushVec = ObjNormal * ((Limit - MeshDis) * Dot);	//�@�������ɉ����o�����������߂�
				Decoration->PushPos(&PushVec);		//1�x�@�������ɉ����o��

				MoveVec = MoveVec + ((2 * Dot) * ObjNormal);			//�ړ��x�N�g����ǂ̖@��������2�񉟂��o���Ĕ��˃x�N�g�������߂Ă���
				
				MoveVec *= 0.8f;		//�����W����ݒ�

				Decoration->SetMoveVec(&MoveVec);
			}
		}
	}


}

void CollisionObserver::EnemyToMapObj(Enemy *Enemy, MapObj *MapObj)
{
	D3DXVECTOR3 TargetVec, ObjPosTmp, EnemyPos;

	EnemyPos = Enemy->GetPos();
	ObjPosTmp = MapObj->GetPos();

	TargetVec = D3DXVECTOR3(EnemyPos.x, 0.0f, EnemyPos.z) - ObjPosTmp;		//Y���W�𖳎�����

	float TargetLength;

	TargetLength = D3DXVec3Length(&TargetVec);

	const float EnemyRadius = Enemy->GetRadisu(), ObjRadius = MapObj->GetRadius();

	if (TargetLength < EnemyRadius + ObjRadius)
	{
		D3DXVec3Normalize(&TargetVec, &TargetVec);
		TargetVec *= (EnemyRadius + ObjRadius - TargetLength);
		D3DXMATRIX TmpMat;

		Enemy->PushedObj(TargetVec);
	}
}

void CollisionObserver::GetPolyNormal(D3DXVECTOR3 *ObjNormal, LPD3DXMESH ObjMesh, const DWORD *PolyNo)
{
	WORD *pI;
	ObjMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	DWORD vertexNo[3];
	vertexNo[0] = *(pI + *PolyNo * 3 + 0);		//PolyNo�Ԗڂ̍\������1�߂̃C���f�b�N�X
	vertexNo[1] = *(pI + *PolyNo * 3 + 1);
	vertexNo[2] = *(pI + *PolyNo * 3 + 2);

	CLONEVERTEX *pV;

	ObjMesh->LockVertexBuffer(0, (LPVOID*)&pV);

	D3DXVECTOR3 vPos[3];

	vPos[0] = (pV + vertexNo[0])->Pos;			//��Ŏ�ɓ��ꂽ�C���f�b�N�X��p���Ă��̒��_�̍��W�𓾂�
	vPos[1] = (pV + vertexNo[1])->Pos;
	vPos[2] = (pV + vertexNo[2])->Pos;

	ObjMesh->UnlockVertexBuffer();

	D3DXVECTOR3 Vec1, Vec2;

	Vec1 = vPos[1] - vPos[0];			//2�ӗp��
	Vec2 = vPos[2] - vPos[0];

	D3DXVec3Cross(ObjNormal, &Vec1, &Vec2);	//�|���S����2�ӂ̊O�ς����ߖ@�������߂�
	D3DXVec3Normalize(ObjNormal, ObjNormal);	//���K��		�����[�J�����W�̖@��

	
}

