#include "GameScene.h"
#include"../MenuScene/MenuScene.h"

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//�d��	���K�����̒l�̂���

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	sceneSwitchState = 1;		//�ŏ��͖��]������

	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	playerCam = new PlayerCamera();
	eventManager = new EventManager();
	decorationManager = new DecorationManager();
	stageBorder = new StageBorder;
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
	resultTex = resourceManager->GetTexture("Result.png", 820, 160, NULL);
	D3DXMatrixTranslation(&resultMat, SCRW / 2, 10, 0);

	returnTex = resourceManager->GetTexture("Click_To_Return.png", 420, 40, NULL);
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
	delete enemyManager;

	delete resultCam;
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

	decorationManager->Draw();
	if (resultFlag == true)
	{
		return;		//�`�悵�Ȃ�		(�C���X�^���X���폜������������񂾂낤���H)��
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	enemyManager->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
	

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

	sceneSwitchEffect->Draw();			//��ɕ`��

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
			sceneSwitcher.SwitchScene(new MenuScene());
			return false;
		}
		return true;		//���U���g�\�����͑������^�[�����ē������~�߂�
	}

	
	if (sceneSwitchState == 1)				//���߂ɖ��]�����鏈��
	{
		if (sceneSwitchEffect->ToBrightness() == true)
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

	player->Update(*snowBallManager, *decorationManager, *pickUpInstructions);		//�J�������X�V���Ă���
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &playerCam->GetmView());		//�J�����̃A�b�v�f�[�g�̌�ɌĂ�

	enemyManager->Update(*player, *snowBallManager, *stageBorder);

	remainingBallUI->SetRemainingBallCnt(player->GetRemainingBalls());
	//remainingBallUI->SetRemainingBallCnt(player->GetHP());		//HP�m�F�p��
	snowBallManager->Update();

	effectManager->SetBillBoardMat(&TmpBillBoardMat);		//��effectManager��Update�̑O�ɌĂ�
	effectManager->Update();

	decorationManager->Updata();

	//��ʂƓG�̓����蔻��
	for (unsigned int ei = 0; ei < enemyManager->enemy.size(); ei++)
	{
		for (unsigned int sj = 0; sj < snowBallManager->snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoEnemy(snowBallManager->snowBall[sj], enemyManager->enemy[ei]) == true)		//������true���Ԃ��Ă���
			{
				//SnowFrag�G�t�F�N�g�Ă�
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[sj]->GetPos()));

				if (enemyManager->enemy[ei]->TakeDamage(1) == false)		//false���Ԃ��Ă�����
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime�Đ��J�n
					//-------------------------------------------------------------
					//�����Ƃ��ēn���ϐ����ꎞ�I�ɐ錾
					D3DXMATRIX TmpAnimeMat;
					XFILE TmpAnimeMesh;
					D3DXVECTOR3 SnowBallVec;

					TmpAnimeMat = enemyManager->enemy[ei]->GetMat();		//�s��
					TmpAnimeMesh = enemyManager->enemy[ei]->GetMesh();	//Mesh
					SnowBallVec = snowBallManager->snowBall[sj]->GetMoveVec();	//��ʂ̈ړ��x�N�g�������炤

					effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));

					//���񂾃C���X�^���X�폜
					delete enemyManager->enemy[ei];
					enemyManager->enemy.erase(enemyManager->enemy.begin() + ei);
					ei--;		//���������l�߂�
				}
				//���񂾃C���X�^���X�폜
				delete snowBallManager->snowBall[sj];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + sj);
				sj--;		//���������l�߂�
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
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[sj]->GetPos()));

				//���񂾃C���X�^���X�폜
				delete snowBallManager->snowBall[sj];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + sj);
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
			effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[si]->GetPos()));
			player->HitSnowBall();			//HIT���̃��\�b�h���Ă�

			delete snowBallManager->snowBall[si];
			snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + si);
			si--;						//���������l�߂�
		}
	}

	for (unsigned int i = 0; i < decorationManager->decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(decorationManager->decoration[i], mapObjManager->mapObj[j], eventManager);
		}
	}
	//----------------------------------------------------------------------------------------
	if (eventManager->Update(*enemyManager, *decorationManager, *stageBorder) == false)		//false���Ԃ��Ă����烊�U���g�ֈڍs����
	{
		sceneSwitchState = -1;
	}

	if (sceneSwitchState == -1)
	{
		if (sceneSwitchEffect->ToDarkness() == true)
		{
			resultFlag = true;
			resultCam = new ResultCam();
			sceneSwitchState = 1;

			//�G��G�t�F�N�g�Ȃǎז��Ȃ��̂��폜����
			enemyManager->AllDelete();
			effectManager->AllDelete();
			snowBallManager->AllDelete();
			decorationManager->DeleteToResult();
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
		if (sceneSwitchEffect->ToBrightness() == true)
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
		if (sceneSwitchEffect->ToDarkness() == true)
		{
			return false;
		}
	}
	return true;
}
