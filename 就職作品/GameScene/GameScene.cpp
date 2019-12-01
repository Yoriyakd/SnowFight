#include "GameScene.h"

EnemyManager *enemyManager;
Player *player;
D3DLIGHT9 Light;
StageBorder *stageBorder;
DecorationManager *decorationManager;
PickUpInstructions *pickUpInstructions;
const float SnowBallGravity = -0.05f;						//�d��	���K�����̒l�̂���

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	collisionObserver = new CollisionObserver();
	playerCam = new PlayerCamera();
	eventManager = new EventManager();
	decorationManager = new DecorationManager();
	pickUpInstructions = new PickUpInstructions();
	remainingBallUI = new RemainingBallUI();


	decorationManager->decoration.push_back(new Decoration_RedBall(&D3DXVECTOR3(80, 0, 50)));		//test��
	decorationManager->decoration.push_back(new Decoration_BlueBall(&D3DXVECTOR3(80, 0, 60)));		//test��
	decorationManager->decoration.push_back(new Decoration_YellowBall(&D3DXVECTOR3(80, 0, 70)));		//test��

	loadStageData->SetStageMap(mapObjManager);
	//-------------------------------------------------------
	//�X�e�[�W�̋��E�����߂�
	//-------------------------------------------------------
	float StageSizeX, StageSizeZ;		//�X�e�[�W�̃T�C�Y	stage�{�[�_�[�����ł悳����
	loadStageData->GetStageSize(&StageSizeX, &StageSizeZ);
	stageBorder = new StageBorder;

	stageBorder->Top = StageSizeZ;
	stageBorder->Bottom = 0;
	stageBorder->Left = 0;
	stageBorder->Right = StageSizeX;
	//-------------------------------------------------------
	playerCam->SetPos(&D3DXVECTOR3(StageSizeX / 2, 0, 10.0f));				//�v���C���[�̏����ʒu

	stage1Enclosure = new Stage1Enclosure(stageBorder);

	player->SetPlayerCamPointer(playerCam);		//�v���C���[�J�����̃|�C���^���Z�b�g

	//-----------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	Light.Diffuse.a = 1.0f;
	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

	Light.Specular.a = 0.8f;
	Light.Specular.r = 0.8f;
	Light.Specular.g = 0.8f;
	Light.Specular.b = 0.8f;

	Light.Ambient.r = 0.3f;
	Light.Ambient.g = 0.3f;
	Light.Ambient.b = 0.3f;

	Light.Range = 1000.0f;

	lpD3DDevice->SetLight(0, &Light);
	lpD3DDevice->LightEnable(0, TRUE);
	//-----------------------------
}

GameScene::~GameScene()
{
	delete loadStageData;
	delete player;
	delete ground;
	delete enemyManager;
	delete skyBox;
	delete stage1Enclosure;
	delete snowBallManager;
	delete mapObjManager;
	delete collisionObserver;
	delete eventManager;
	delete pickUpInstructions;
}

void GameScene::Render3D(void)
{
	skyBox->Draw();
	ground->Draw();
	stage1Enclosure->Draw();
	mapObjManager->Draw();
	enemyManager->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
	decorationManager->Draw();

	player->Draw();		//��Z�o�b�t�@�N���A�����Ă��邽�ߍŌ�ɕ`�悷��
}

void GameScene::SetCamera(void)
{
	playerCam->SetCamera();
}

void GameScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	pickUpInstructions->Draw();
	remainingBallUI->Draw();

	// �`��I��
	lpSprite->End();
}

bool GameScene::Update()
{
	playerCam->Update();
	//�}�b�v�I�u�W�F�ƃv���C���[�̓����蔻��
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		collisionObserver->PlayertoObj(playerCam, mapObjManager->mapObj[i]);
	}

	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &playerCam->GetmView());		//�J�����̃A�b�v�f�[�g�̌�ɌĂ�

	enemyManager->Update(snowBallManager);

	player->Update(snowBallManager);		//�J�������X�V���Ă���
	remainingBallUI->SetRemainingBallCnt(player->GetRemainingBalls());
	//remainingBallUI->SetRemainingBallCnt(player->GetHP());		//HP�m�F�p��
	snowBallManager->Update();

	effectManager->SetBillBoardMat(&TmpBillBoardMat);		//��effectManager��Update�̑O�ɌĂ�
	effectManager->Update();

	eventManager->Update();
	decorationManager->Updata();

	//��ʂƓG�̓����蔻��
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			if (snowBallManager->snowBall[j]->GetID() == PLAYER_ID)		//�v���C���[�̋��Ȃ���s
			{
				if (collisionObserver->SnowBalltoEnemy(snowBallManager->snowBall[j], enemyManager->enemy[i]) == true)		//������true���Ԃ��Ă���
				{
					//SnowFrag�G�t�F�N�g�Ă�
					effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[j]->GetPos()));

					if (enemyManager->enemy[i]->TakeDamage(1) == false)		//false���Ԃ��Ă�����
					{
						//-------------------------------------------------------------
						//EnemyDeathAnime�Đ��J�n
						//-------------------------------------------------------------
						//�����Ƃ��ēn���ϐ����ꎞ�I�ɐ錾
						D3DXMATRIX TmpAnimeMat;
						XFILE TmpAnimeMesh;
						D3DXVECTOR3 SnowBallVec;

						TmpAnimeMat = enemyManager->enemy[i]->GetMat();		//�s��
						TmpAnimeMesh = enemyManager->enemy[i]->GetMesh();	//Mesh
						SnowBallVec = snowBallManager->snowBall[j]->GetMoveVec();	//��ʂ̈ړ��x�N�g�������炤

						effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));

						//���񂾃C���X�^���X�폜
						delete enemyManager->enemy[i];
						enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
						i--;		//���������l�߂�
					}
					//���񂾃C���X�^���X�폜
					delete snowBallManager->snowBall[j];
					snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
					j--;		//���������l�߂�
				}
			}
		}
	}

	//��ʂƃ}�b�v�I�u�W�F�̓����蔻��

	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			if (collisionObserver->SnowBalltoObj(snowBallManager->snowBall[j], mapObjManager->mapObj[i]))		//������true���Ԃ��Ă���
			{
				//SnowFrag�G�t�F�N�g�Ă�
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[j]->GetPos()));

				//���񂾃C���X�^���X�폜
				delete snowBallManager->snowBall[j];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
				j--;				//���������l�߂�
			}
		}
	}

	//�G�̐�ʂƃv���C���[�̂����蔻��
	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		if (snowBallManager->snowBall[i]->GetID() == ENEMY_ID)		//�G�̋��Ȃ���s
		{
			if (collisionObserver->EnemySnowBalltoPlayer(player, snowBallManager->snowBall[i]))
			{
				//SnowFrag�G�t�F�N�g�Ă�
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[i]->GetPos()));
				player->HitSnowBall();			//HIT���̃��\�b�h���Ă�

				delete snowBallManager->snowBall[i];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
				i--;						//���������l�߂�
			}
		}
	}

	for (unsigned int i = 0; i < decorationManager->decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			collisionObserver->DecorationToMapObj(decorationManager->decoration[i], mapObjManager->mapObj[j]);
		}
	}

	return true;
}
