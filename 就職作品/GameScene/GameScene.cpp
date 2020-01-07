#include "GameScene.h"
#include"../MenuScene/MenuScene.h"

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//�d��	���K�����̒l�̂���

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	sceneSwitchState = 1;		//�ŏ��͖��]������

	GetEnemyManager.Create();
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	playerCam = new PlayerCamera();
	eventManager = new EventManager();
	
	GetDecorationManager.Create();
	GetSpawnerManager.Create();

	stageBorder = new StageBorder;
	EnemyAnime.Create();
	//-------------------------------------------------------
	//UI
	//-------------------------------------------------------
	pickUpInstructions = new PickUpInstructions();
	remainingBallUI = new RemainingBallUI();
	timeUI = new TimeUI();
	gameObjective = new GameObjective();

	//-------------------------------------------------------
	//���U���g
	//-------------------------------------------------------
	resultTex = GetResource.GetTexture(ResultHead_Tex);
	D3DXMatrixTranslation(&resultMat, SCRW / 2, 10, 0);

	returnTex = GetResource.GetTexture(ResultReturn_Tex);
	D3DXMatrixTranslation(&returnMat, 800, 500, 0);


	loadStageData->SetStageMap(*mapObjManager, *eventManager, *gameObjective, *stageBorder);
	
	//-------------------------------------------------------
	playerCam->SetPos(&D3DXVECTOR3(stageBorder->Right / 2, 0, 10.0f));				//�v���C���[�̏����ʒu

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
	delete ground;
	delete skyBox;
	delete stage1Enclosure;
	delete snowBallManager;
	delete mapObjManager;
	delete playerCam;
	delete eventManager;

	delete player;
	GetEnemyManager.Destroy();

	delete resultCam;

	GetDecorationManager.Destroy();
	GetSpawnerManager.Destroy();
	EnemyAnime.Destroy();
	//-------------------------------------------------------
	//UI
	//-------------------------------------------------------
	delete pickUpInstructions;
	delete remainingBallUI;
	delete timeUI;
	delete gameObjective;
}

void GameScene::Render3D(void)
{
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	skyBox->Draw();
	ground->Draw();
	stage1Enclosure->Draw();
	mapObjManager->Draw();

	GetDecorationManager.Draw();
	if (resultFlag == true)
	{
		return;		//�`�悵�Ȃ�		(�C���X�^���X���폜������������񂾂낤���H)��
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	GetEnemyManager.Draw();
	EnemyAnime.Draw();
	snowBallManager->Draw();
	Effect.Draw();
	

	player->Draw();		//��Z�o�b�t�@�N���A�����Ă��邽�ߍŌ�ɕ`�悷��
}

void GameScene::SetCamera(void)
{
	if (resultFlag == true)
	{
		resultCam->SetCamera();				//���U���g���̃J����
		return;
	}
	playerCam->SetCamera();
}

void GameScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (resultFlag == false)		//���U���g�\�����͏���
	{
		pickUpInstructions->Draw();
		remainingBallUI->Draw();
		timeUI->Draw();
		gameObjective->Draw();
	}
	else
	{
		RECT RcResult = { 0, 0, 820, 160 };
		lpSprite->SetTransform(&resultMat);
		lpSprite->Draw(resultTex, &RcResult, &D3DXVECTOR3(820 / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT RcReturn = { 0, 0, 420, 40 };
		lpSprite->SetTransform(&returnMat);
		lpSprite->Draw(returnTex, &RcResult, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SceneSwitch.Draw();			//��ɕ`��

	// �`��I��
	lpSprite->End();
}

bool GameScene::Update()
{
	//---------------------------------------------------------
	//���U���g���̏���
	//---------------------------------------------------------
	if (resultFlag == true)
	{
		if (ResultUpdate() == false)			//���U���g���̏����͂����ɋL�q
		{
			SwitcheScene.SwitchScene(new MenuScene());
			return false;
		}
		return true;		//���U���g�\�����͑������^�[�����ē������~�߂�
	}


	if (sceneSwitchState == 1)				//���߂ɖ��]�����鏈��
	{
		if (SceneSwitch.ToBrightness() == true)
		{
			sceneSwitchState = 0;
		}
	}
	//----------------------------------------------------------------------------------------------------------------
	//�v���C���[�̍X�V	���J�����������蔻�聨�v���C���[�̏��Ԃ�	�v���C���[�̂̈ʒu���J�����Ƃ���邽��
	//----------------------------------------------------------------------------------------------------------------
	playerCam->Update(*stageBorder);						//�v���C���[�J�����̈ړ�

	//�}�b�v�I�u�W�F�ƃv���C���[�̓����蔻��
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		CollisionObserver::PlayertoObj(playerCam, mapObjManager->mapObj[i]);
	}

	player->Update(*snowBallManager, GetDecorationManager, *pickUpInstructions);		//�J�������X�V���Ă���
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &playerCam->GetmView());		//�J�����̃A�b�v�f�[�g�̌�ɌĂ�

	GetEnemyManager.Update(*player, *snowBallManager, *stageBorder);

	remainingBallUI->SetRemainingBallCnt(player->GetRemainingBalls());
	//remainingBallUI->SetRemainingBallCnt(player->GetHP());		//HP�m�F�p��
	snowBallManager->Update();

	Effect.SetBillBoardMat(&TmpBillBoardMat);		//��effectManager��Update�̑O�ɌĂ�
	Effect.Update();
	EnemyAnime.Updata();

	GetDecorationManager.Updata();

	//��ʂƓG�̓����蔻��
	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int sj = 0; sj < snowBallManager->snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoEnemyHat(snowBallManager->snowBall[sj], GetEnemyManager.enemy[ei]) == true)
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(10) == false)		//false���Ԃ��Ă�����
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime�쐬
					//-------------------------------------------------------------
					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj], true);

					//���񂾃C���X�^���X�폜
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//���������l�߂�

					//SnowFrag�G�t�F�N�g�Ă�
					Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

					//���񂾃C���X�^���X�폜
					snowBallManager->DeleteInstance(sj);
					sj--;		//���������l�߂�

					break;
				}
				
			}

			if (CollisionObserver::SnowBalltoEnemy(snowBallManager->snowBall[sj], GetEnemyManager.enemy[ei]) == true)		//������true���Ԃ��Ă���
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(1) == false)		//false���Ԃ��Ă�����
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime�쐬
					//-------------------------------------------------------------

					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj], false);

					//���񂾃C���X�^���X�폜
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//���������l�߂�
				}

				//SnowFrag�G�t�F�N�g�Ă�
				Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

				//���񂾃C���X�^���X�폜
				snowBallManager->DeleteInstance(sj);
				sj--;		//���������l�߂�

				break;
			}
		}
	}

	//��ʂƃ}�b�v�I�u�W�F�̓����蔻��

	for (unsigned int mi = 0; mi < mapObjManager->mapObj.size(); mi++)
	{
		for (unsigned int sj = 0; sj < snowBallManager->snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoObj(snowBallManager->snowBall[sj], mapObjManager->mapObj[mi]))		//������true���Ԃ��Ă���
			{
				//SnowFrag�G�t�F�N�g�Ă�
				Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

				//���񂾃C���X�^���X�폜
				snowBallManager->DeleteInstance(sj);
				sj--;				//���������l�߂�
			}
		}
	}

	//�G�̐�ʂƃv���C���[�̂����蔻��
	for (unsigned int si = 0; si < snowBallManager->snowBall.size(); si++)
	{
		if (CollisionObserver::EnemySnowBalltoPlayer(player, snowBallManager->snowBall[si]))
		{
			//SnowFrag�G�t�F�N�g�Ă�
			Effect.NewSnowFrag(snowBallManager->snowBall[si]->GetPos());
			player->HitSnowBall();			//HIT���̃��\�b�h���Ă�

			snowBallManager->DeleteInstance(si);
			si--;						//���������l�߂�
		}
	}

	for (unsigned int i = 0; i < GetDecorationManager.decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(GetDecorationManager.decoration[i], mapObjManager->mapObj[j], eventManager);
		}
	}

	GetSpawnerManager.Update(*stageBorder);
	//----------------------------------------------------------------------------------------
	if (eventManager->Update(GetEnemyManager, GetDecorationManager, *stageBorder) == false)		//false���Ԃ��Ă����烊�U���g�ֈڍs����
	{
		sceneSwitchState = -1;
	}

	if (sceneSwitchState == -1)
	{
		if (SceneSwitch.ToDarkness() == true)
		{
			resultFlag = true;
			resultCam = new ResultCam();
			sceneSwitchState = 1;

			//�G��G�t�F�N�g�Ȃǎז��Ȃ��̂��폜����
			GetEnemyManager.AllDelete();
			Effect.AllDelete();
			snowBallManager->AllDelete();
			GetDecorationManager.DeleteToResult();
		}
	}
	//----------------------------------------------------------------------------------------
	timeUI->SetTime_s(eventManager->GetRemainingTime_s());
	bool NormState;

	NormState = eventManager->GetNormState();
	if (NormState == false)
	{
		gameObjective->SetNowNormCnt(eventManager->GetNowNormCnt());
	}
	else
	{
		gameObjective->SetNormState(eventManager->GetNormState());
	}

	return true;
}

bool GameScene::ResultUpdate(void)
{
	if (sceneSwitchState == 1)				//�V�[���ڍs�㖾�]�����鏈��
	{
		if (SceneSwitch.ToBrightness() == true)
		{
			sceneSwitchState = 0;
		}
	}

	resultCam->Update(&mapObjManager->GetXmasTreePos());

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		sceneSwitchState = -1;
	}

	if (sceneSwitchState == -1)
	{
		if (SceneSwitch.ToDarkness() == true)
		{
			return false;
		}
	}
	return true;
}
