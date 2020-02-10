#include "GameScene.h"
#include"../MenuScene/MenuScene.h"
#include"../TitleScene/TitleScene.h"

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//�d��	���K�����̒l�̂���

GameScene::GameScene(int StageNo): isESCKye(false), Resultime(120), isSwitchResulut(false), endSceneState(false)
{
	GetResource.GetXFILE(EnemyBody_M);
	GetResource.GetXFILE(EnemyHand_M);
	GetResource.GetXFILE(EnemyHat_M);/*1�x�ǂݍ��ނ��ƂŌy�ʉ�*/

	srand(timeGetTime());

	GetEnemyManager.Create();
	loadStageData = new LoadStageData(StageNo);
	ground = new Ground;
	
	skyBox = new SkyBox;
	GetSnowBallManager.Create();
	mapObjManager = new MapObjManager();
	GetPlayerCam.Create();
	eventManager = new EventManager();

	GetPlayer.Create();
	
	GetDecorationManager.Create();
	GetSpawnerManager.Create();

	for (auto i = 0; i < EFFECT_CNT; i++)
	{
		playerHitEffect_Right[i] = new PlayerHitEffect();
		playerHitEffect_Right[i]->Initialize_RightEffect();
	}

	for (auto i = 0; i < EFFECT_CNT; i++)
	{
		playerHitEffect_Left[i] = new PlayerHitEffect();
		playerHitEffect_Left[i]->Initialize_LeftEffect();
	}

	playerHitEffect_Back = new PlayerHitEffect();
	playerHitEffect_Back->Initialize_BackEffect();

	stageBorder = new StageBorder;
	EnemyAnime.Create();
	//-------------------------------------------------------
	//UI
	//-------------------------------------------------------
	pickUpInstructions = new PickUpInstructions();
	remainingBallUI = new RemainingBallUI();
	timeUI = new TimeUI();
	gameObjective = new GameObjective();
	AddSnowBallUI::GetInstance().Create();

	//-------------------------------------------------------
	//���U���g
	//-------------------------------------------------------
	resultTex = GetResource.GetTexture(ResultHead_Tex);
	D3DXMatrixTranslation(&resultMat, SCRW / 2, 10, 0);

	returnTex = GetResource.GetTexture(ResultReturn_Tex);
	D3DXMatrixTranslation(&returnMat, 800, 500, 0);


	loadStageData->SetStageMap(*mapObjManager, *eventManager, *gameObjective, *stageBorder);
	
	//-------------------------------------------------------
	GetPlayerCam.SetPos(&D3DXVECTOR3(stageBorder->Right / 2, 0, 10.0f));				//�v���C���[�̏����ʒu

	stage1Enclosure = new Stage1Enclosure(stageBorder);


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
	StartScene();
}

GameScene::~GameScene()
{
	delete loadStageData;
	delete ground;
	delete skyBox;
	delete stage1Enclosure;
	GetSnowBallManager.Destroy();
	delete mapObjManager;
	GetPlayerCam.Destroy();
	delete eventManager;

	GetPlayer.Destroy();
	GetEnemyManager.Destroy();

	delete resultCam;

	for (auto PlayerHitEffect_Right : playerHitEffect_Right)
	{
		delete PlayerHitEffect_Right;
		
	}

	for (auto PlayerHitEffect_Left : playerHitEffect_Left)
	{
		delete PlayerHitEffect_Left;
	}

	delete playerHitEffect_Back;

	delete stageBorder;

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
	AddSnowBallUI::GetInstance().Destroy();
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
	GetSnowBallManager.Draw();
	Effect.Draw();
	

	GetPlayer.Draw();		//��Z�o�b�t�@�N���A�����Ă��邽�ߍŌ�ɕ`�悷��
}

void GameScene::SetCamera(void)
{
	if (resultFlag == true)
	{
		resultCam->SetCamera();				//���U���g���̃J����
		return;
	}
	GetPlayerCam.SetCamera();
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
		for (auto PlayerHitEffect_Right : playerHitEffect_Right)
		{
			PlayerHitEffect_Right->Draw();
		}

		for (auto PlayerHitEffect_Left : playerHitEffect_Left)
		{
			PlayerHitEffect_Left->Draw();
		}

		playerHitEffect_Back->Draw();

		pickUpInstructions->Draw();
		remainingBallUI->Draw();
		timeUI->Draw();
		for (auto *TimePenaltyUI : timePenaltyUI)
		{
			TimePenaltyUI->Draw();
		}
		gameObjective->Draw();

		AddSnowBallUI::GetInstance().Draw();
	}
	else
	{
		RECT RcResult = { 0, 0, 820, 160 };
		lpSprite->SetTransform(&resultMat);
		lpSprite->Draw(resultTex, &RcResult, &D3DXVECTOR3(820 / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT RcReturn = { 0, 0, 499, 84 };
		if (Resultime <= 0)
		{
			lpSprite->SetTransform(&returnMat);
			lpSprite->Draw(returnTex, &RcReturn, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	GetBackToTitle.Draw();
	GetSceneSwitchEffect.Draw();			//��ɕ`��

	// �`��I��
	lpSprite->End();
}

bool GameScene::Update()
{
	static bool BackToTitleFlag = false;
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) || BackToTitleFlag == true)
	{
		if (isESCKye == true)
		{
			BackToTitleFlag = true;
			int State;

			State = GetBackToTitle.CallBackToTitle();
			switch (State)
			{
			case -1:
				BackToTitleFlag = false;
				isESCKye = false;		//�������ςȂ��΍�
				break;
			case 0:
				return true;
				break;
			case 1:
				BackToTitleFlag = false;
				EndScene();
				break;
			}
		}
	}
	else
	{
		isESCKye = true;
	}

	if (endSceneState == true)
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)		//�V�[���J�ڂ��I����Ă�����ڍs
		{
			GetSceneSwitcher.SwitchScene(new TitleScene());			//�^�C�g���ֈڍs
			return false;
		}
		return true;
	}

	//---------------------------------------------------------
	//���U���g�ڍs
	//---------------------------------------------------------
	if (isSwitchResulut == true)
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			StartResult();
		}
	}

	//---------------------------------------------------------
	//���U���g���̏���
	//---------------------------------------------------------
	if (resultFlag == true)
	{
		if (ResultUpdate() == false)			//���U���g���̏����͂����ɋL�q
		{
			GetSceneSwitcher.SwitchScene(new MenuScene());
			GetSound.AllStop();
			return false;
		}
		return true;		//���U���g�\�����͑������^�[�����ē������~�߂�
	}

	//----------------------------------------------------------------------------------------------------------------
	//�v���C���[�̍X�V	���J�����������蔻�聨�v���C���[�̏��Ԃ�	�v���C���[�̂̈ʒu���J�����Ƃ���邽��
	//----------------------------------------------------------------------------------------------------------------
	GetPlayerCam.Update(*stageBorder);						//�v���C���[�J�����̈ړ�

	//�}�b�v�I�u�W�F�ƃv���C���[�̓����蔻��
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		CollisionObserver::PlayertoObj(&GetPlayerCam, mapObjManager->mapObj[i]);
	}

	GetPlayer.Update(*pickUpInstructions);		//�J�������X�V���Ă���

	AddSnowBallUI::GetInstance().Update();
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &GetPlayerCam.GetmView());		//�J�����̃A�b�v�f�[�g�̌�ɌĂ�

	GetEnemyManager.Update(GetSnowBallManager, *stageBorder);

	remainingBallUI->SetRemainingBallCnt(GetPlayer.GetRemainingBalls());
	GetSnowBallManager.Update();

	Effect.SetBillBoardMat(&TmpBillBoardMat);		//��effectManager��Update�̑O�ɌĂ�
	Effect.Update();
	EnemyAnime.Updata();

	GetDecorationManager.Updata();

	//��ʂƓG�̓����蔻��
	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int sj = 0; sj < GetSnowBallManager.snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoEnemyHat(GetSnowBallManager.snowBall[sj], GetEnemyManager.enemy[ei]) == true)
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(10) == false)		//false���Ԃ��Ă�����
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime�쐬
					//-------------------------------------------------------------
					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj], true);

					//���񂾃C���X�^���X�폜
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//���������l�߂�

					//SnowFrag�G�t�F�N�g�Ă�
					Effect.NewSnowFrag(GetSnowBallManager.snowBall[sj]->GetPos());

					//���񂾃C���X�^���X�폜
					GetSnowBallManager.DeleteInstance(sj);
					sj--;		//���������l�߂�

					break;
				}
				
			}

			if (CollisionObserver::SnowBalltoEnemy(GetSnowBallManager.snowBall[sj], GetEnemyManager.enemy[ei]) == true)		//������true���Ԃ��Ă���
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(1) == false)		//false���Ԃ��Ă�����
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime�쐬
					//-------------------------------------------------------------

					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj], false);

					//���񂾃C���X�^���X�폜
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//���������l�߂�
				}

				//SnowFrag�G�t�F�N�g�Ă�
				Effect.NewSnowFrag(GetSnowBallManager.snowBall[sj]->GetPos());

				//���񂾃C���X�^���X�폜
				GetSnowBallManager.DeleteInstance(sj);
				sj--;		//���������l�߂�

				break;
			}
		}
	}

	//��ʂƃ}�b�v�I�u�W�F�̓����蔻��

	for (unsigned int mi = 0; mi < mapObjManager->mapObj.size(); mi++)
	{
		for (unsigned int sj = 0; sj < GetSnowBallManager.snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoObj(GetSnowBallManager.snowBall[sj], mapObjManager->mapObj[mi]))		//������true���Ԃ��Ă���
			{
				//SnowFrag�G�t�F�N�g�Ă�
				Effect.NewSnowFrag(GetSnowBallManager.snowBall[sj]->GetPos());

				//���񂾃C���X�^���X�폜
				GetSnowBallManager.DeleteInstance(sj);
				sj--;				//���������l�߂�
			}
		}
	}

	//�G�̐�ʂƃv���C���[�̂����蔻��
	for (unsigned int si = 0; si < GetSnowBallManager.snowBall.size(); si++)
	{
		if (CollisionObserver::EnemySnowBalltoPlayer(&GetPlayer, GetSnowBallManager.snowBall[si]))
		{
			//SnowFrag�G�t�F�N�g�Ă�
			Effect.NewSnowFrag(GetSnowBallManager.snowBall[si]->GetPos());
			eventManager->PlayerTakeDamage();			//HIT���̃��\�b�h���Ă�
			timePenaltyUI.push_back(new TimePenaltyUI(3));		//�ϐ���

			//Sound���Ă�
			GetSound.Play2D(SnowBallHit_SOUND);

			//----------------------------------------------------
			//HitEffecct�̏���(Effect�̃N���X�ɕϐ��������������������̂ł́H)
			//----------------------------------------------------
			HitEffectID ActivationID;

			ActivationID = PlayerHitEffect::CalculateHitDirection(GetSnowBallManager.snowBall[si]->GetMoveVec());

			switch (ActivationID)
			{
			case Right:
				for (auto PlayerHitEffect_Right : playerHitEffect_Right)
				{
					if (PlayerHitEffect_Right->GetActiveState() == false)
					{
						PlayerHitEffect_Right->Active();
						break;
					}
				}
				break;
			case Left:
				for (auto PlayerHitEffect_Left: playerHitEffect_Left)
				{
					if (PlayerHitEffect_Left->GetActiveState() == false)
					{
						PlayerHitEffect_Left->Active();
						break;
					}
				}
				break;
			case Back:
				playerHitEffect_Back->Active();
				break;
			}

			//----------------------------------------------------
			GetSnowBallManager.DeleteInstance(si);
			si--;						//���������l�߂�
		}
	}

	for (auto PlayerHitEffect_Right : playerHitEffect_Right)
	{
		PlayerHitEffect_Right->Update();
	}

	for (auto PlayerHitEffect_Left : playerHitEffect_Left)
	{
		PlayerHitEffect_Left->Update();
	}

	playerHitEffect_Back->Update();

	//�f�R���[�V������MapObj�̓����蔻��
	for (unsigned int i = 0; i < GetDecorationManager.decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(GetDecorationManager.decoration[i], mapObjManager->mapObj[j], eventManager);
		}
	}

	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int mj = 0; mj < mapObjManager->mapObj.size(); mj++)
		{
			CollisionObserver::EnemyToMapObj(GetEnemyManager.enemy[ei], mapObjManager->mapObj[mj]);
		}
	}
	for (unsigned int i = 0; i < timePenaltyUI.size(); i++)
	{
		if (timePenaltyUI[i]->Update() == false)
		{
			delete timePenaltyUI[i];
			timePenaltyUI.erase(timePenaltyUI.begin() + i);
			i--;
		}

	}
	GetSpawnerManager.Update(*stageBorder);
	//----------------------------------------------------------------------------------------
	//�C�x���g����
	//----------------------------------------------------------------------------------------
	if (eventManager->Update() == false)		//false���Ԃ��Ă����烊�U���g�ֈڍs����
	{
		SwitchResulut();
	}

	//----------------------------------------------------------------------------------------
	//���ԏ���
	//----------------------------------------------------------------------------------------
	timeUI->SetTime_s(eventManager->GetRemainingTime_s());		//�t���[����b�ɒ����ēn���Ă���
	timeUI->Update();

	//----------------------------------------------------------------------------------------
	//�m���}����
	//----------------------------------------------------------------------------------------
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

void GameScene::StartScene()
{
	GetSound.Play2D(InGameBGM_SOUND);
	GetSceneSwitchEffect.PlayFadeIn();
}

void GameScene::EndScene()
{
	GetSceneSwitchEffect.PlayFadeOut();
	GetSound.AllStop();										//�T�E���h���Đ���~
	endSceneState = true;
}

void GameScene::SwitchResulut()
{
	GetSceneSwitchEffect.PlayFadeOut();
	isSwitchResulut = true;
}

void GameScene::StartResult(void)
{
	//�G��G�t�F�N�g�Ȃǎז��Ȃ��̂��폜����
	GetEnemyManager.AllDelete();
	Effect.AllDelete();
	GetSnowBallManager.AllDelete();
	GetDecorationManager.DeleteToResult();

	resultFlag = true;
	isSwitchResulut = false;
	GetSceneSwitchEffect.PlayFadeIn();
	resultFlag = true;
	resultCam = new ResultCam();
}

void GameScene::EndResult(void)
{
	GetSceneSwitchEffect.PlayFadeOut();
	endResultState = true;
}

//���̕ӂ�͍�蒼���̕K�v����
bool GameScene::ResultUpdate(void)
{
	resultCam->Update(&mapObjManager->GetXmasTreePos());

	Resultime--;

	if (Resultime <= 0)//��莞�ԓ��͂��������Ȃ�
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//�E�N���b�N���������ƃV�[���J��
		{
			EndResult();
		}
	}

	if (endResultState == true)		//���U���g�I���t���O�������Ă����ԂŃt�F�[�h���I������ƃV�[���J��
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			return false;
		}
	}
	return true;
}
