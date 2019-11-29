#include "CollisionObserver.h"

CollisionObserver::CollisionObserver()
{
}

CollisionObserver::~CollisionObserver()
{
}

void CollisionObserver::SnowBalltoEnemy(SnowBallManager *SnowBallManager, EnemyManager *EnemyManager)
{
	for (unsigned int i = 0; i < EnemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < SnowBallManager->snowBall.size(); j++)
		{
			if (SnowBallManager->snowBall[j]->GetID() == PLAYER_ID)		//�v���C���[�̋��Ȃ���s
			{

				//---------------------------------------------------------------
				//�K�v�Ȓl��p��

				CollisionSphere SnowBallSphre, EnemySphreA, EnemySphreB;//A����B����

				EnemyManager->enemy[i]->GetCollisionSphere(&EnemySphreA, &EnemySphreB);		/*�����蔻��̋��̃f�[�^�擾*/
				SnowBallManager->snowBall[j]->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
				//---------------------------------------------------------------

				if (CollisionDetection(&SnowBallSphre, &EnemySphreA) || CollisionDetection(&SnowBallSphre, &EnemySphreB))
				{
					//SnowFrag�G�t�F�N�g�Ă�
					effectManager->snowFrag.push_back(new SnowFrag(SnowBallManager->snowBall[j]->GetPos()));

					if (EnemyManager->enemy[i]->TakeDamage(1) == false)		//false���Ԃ��Ă�����
					{
						//-------------------------------------------------------------
						//EnemyDeathAnime�Đ��J�n
						//-------------------------------------------------------------
						//�����Ƃ��ēn���ϐ����ꎞ�I�ɐ錾
						D3DXMATRIX TmpAnimeMat;
						XFILE TmpAnimeMesh;
						D3DXVECTOR3 SnowBallVec;

						TmpAnimeMat = EnemyManager->enemy[i]->GetMat();		//�s��
						TmpAnimeMesh = EnemyManager->enemy[i]->GetMesh();	//Mesh
						SnowBallVec = SnowBallManager->snowBall[j]->GetMoveVec();	//��ʂ̈ړ��x�N�g�������炤

						effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));
						//-------------------------------------------------------------

						//���񂾃C���X�^���X�폜
						delete EnemyManager->enemy[i];
						EnemyManager->enemy.erase(EnemyManager->enemy.begin() + i);
						i--;						//���������l�߂�
					}

					delete SnowBallManager->snowBall[j];
					SnowBallManager->snowBall.erase(SnowBallManager->snowBall.begin() + j);
					j--;						//���������l�߂�
					break;
				}
			}
		}
	}
}

void CollisionObserver::SnowBalltoObj(SnowBallManager *SnowBallManager, MapObjManager *MapObjManager)
{
	for (unsigned int i = 0; i < SnowBallManager->snowBall.size(); i++)
	{
		for (unsigned int j = 0; j < MapObjManager->mapObj.size(); j++)
		{
			//---------------------------------------------------------------
			//�K�v�Ȓl��p��

			XFILE MeshTmp;
			D3DXMATRIX MeshMat;
			D3DXVECTOR3 RayVec, RayPos;
			float MeshDis;

			MeshTmp = MapObjManager->mapObj[j]->GetMesh();
			MeshMat = MapObjManager->mapObj[j]->GetMat();
			RayPos = SnowBallManager->snowBall[i]->GetPos();
			RayVec = SnowBallManager->snowBall[i]->GetMoveVec();
			D3DXVec3Normalize(&RayVec, &RayVec);

			//---------------------------------------------------------------

			if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//���b�V���ɑ΂��ă��C����
			{
				CollisionSphere SnowBallSphere;
				SnowBallManager->snowBall[i]->GetCollisionSphere(&SnowBallSphere);

				if (MeshDis < SnowBallSphere.radius)										//���������a�ȉ��Ȃ�
				{
					//SnowFrag�G�t�F�N�g�Ă�
					effectManager->snowFrag.push_back(new SnowFrag(SnowBallManager->snowBall[i]->GetPos()));

					//���񂾃C���X�^���X�폜
					delete SnowBallManager->snowBall[i];
					SnowBallManager->snowBall.erase(SnowBallManager->snowBall.begin() + i);
					i--;				//���������l�߂�
					break;
				}
			}
		}
	}
}

void CollisionObserver::PlayertoObj(PlayerCamera * PlayerCam, MapObjManager * MapObjManager)
{
	D3DXVECTOR3 PlayerPosTmp, PlayerMoveVecTmp;
	PlayerPosTmp = PlayerCam->GetPos();
	PlayerPosTmp.y = 0;				//Y���W�����̈ʒu�Ȃ̂ŕύX
	PlayerMoveVecTmp = PlayerCam->GetmoveVec();

	for (unsigned int i = 0; i < MapObjManager->mapObj.size(); i++)
	{
		

		CollisionDetectionType TypeTmp;
		TypeTmp = MapObjManager->mapObj[i]->GetCollisionDetectionType();

		if (TypeTmp == Ray)				//�݌v����邷����	��
		{
			D3DXMATRIX ObjMatTmp;
			ObjMatTmp = MapObjManager->mapObj[i]->GetMat();
			D3DXMATRIX invMat;

			D3DXMatrixInverse(&invMat, NULL, &ObjMatTmp);

			D3DXVECTOR3 LocalPos, LocalVec;

			D3DXVec3TransformCoord(&LocalPos, &PlayerPosTmp, &invMat);		//���ꂼ��̋t�s������
			D3DXVec3TransformNormal(&LocalVec, &PlayerMoveVecTmp, &invMat);
			D3DXVec3Normalize(&LocalVec, &LocalVec);


			BOOL hit; float meshDis; DWORD PolyNo; XFILE ObjMesh;

			ObjMesh = MapObjManager->mapObj[i]->GetMesh();

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
				ObjPosTmp = MapObjManager->mapObj[i]->GetPos();

				TargetVec = D3DXVECTOR3(PlayerPosTmp.x, 0.0f, PlayerPosTmp.z) - ObjPosTmp;		//Y���W�𖳎�����

				float TargetLength;

				TargetLength = D3DXVec3Length(&TargetVec);

				const float PlayerRadius = 2.0f, ObjRadius = MapObjManager->mapObj[i]->GetRadius();

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
}

void CollisionObserver::EnemySnowBalltoPlayer(Player * Player, SnowBallManager * SnowBallManager)
{
	for (unsigned int j = 0; j < SnowBallManager->snowBall.size(); j++)
	{
		if (SnowBallManager->snowBall[j]->GetID() == ENEMY_ID)		//�G�̋��Ȃ���s
		{

			//---------------------------------------------------------------
			//�K�v�Ȓl��p��

			CollisionSphere SnowBallSphre, PlayerSphre;

			Player->GetCollisionSphere(&PlayerSphre);									/*�����蔻��̋��̃f�[�^�擾*/
			SnowBallManager->snowBall[j]->GetCollisionSphere(&SnowBallSphre);			/*�����蔻��̋��̃f�[�^�擾*/
			//---------------------------------------------------------------

			if (CollisionDetection(&SnowBallSphre, &PlayerSphre))
			{
				//SnowFrag�G�t�F�N�g�Ă�
				effectManager->snowFrag.push_back(new SnowFrag(SnowBallManager->snowBall[j]->GetPos()));
				Player->HitSnowBall();			//HIT���̃��\�b�h���Ă�

				delete SnowBallManager->snowBall[j];
				SnowBallManager->snowBall.erase(SnowBallManager->snowBall.begin() + j);
				j--;						//���������l�߂�
				break;
			}
		}
	}
}

void CollisionObserver::DecorationToMapObj(DecorationManager * DecorationManager, MapObjManager * MapObjManager)
{
	for (unsigned int i = 0; i < DecorationManager->decoration.size(); i++)
	{
		for (unsigned int j = 0; j < MapObjManager->mapObj.size(); j++)
		{
			//---------------------------------------------------------------
			//�K�v�Ȓl��p��

			XFILE MeshTmp;
			D3DXMATRIX MeshMat;
			D3DXVECTOR3 RayVec, RayPos;
			float MeshDis;

			MeshTmp = MapObjManager->mapObj[j]->GetMesh();
			MeshMat = MapObjManager->mapObj[j]->GetMat();
			RayPos = DecorationManager->decoration[i]->GetPos();
			RayVec = DecorationManager->decoration[i]->GetMoveVec();
			D3DXVec3Normalize(&RayVec, &RayVec);

			//---------------------------------------------------------------

			if (MeshCollisionDetection(&MeshTmp, &MeshMat, &RayPos, &RayVec, &MeshDis))			//���b�V���ɑ΂��ă��C����
			{
				float Radius = 3.0f;

				if (MeshDis < Radius)										//���������a�ȉ��Ȃ�
				{

					break;
				}
			}
		}
	}
}
