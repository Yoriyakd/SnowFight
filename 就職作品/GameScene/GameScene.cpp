#include "GameScene.h"
#include"../MenuScene/MenuScene.h"
#include"../TitleScene/TitleScene.h"
#include"../DirectX/Direct3D.h"
#include"../DirectX/Sprite.h"
#include <algorithm>

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//�d��	���K�����̒l�̂���

GameScene::GameScene(int StageNo):ResulCnt(120)
{
	GetResource.GetXFILE(EnemyBody_M);
	GetResource.GetXFILE(EnemyHand_M);
	GetResource.GetXFILE(EnemyHat_M);
	GetResource.GetXFILE(Decoration_BlueBall_M);
	GetResource.GetXFILE(Decoration_RedBall_M);
	GetResource.GetXFILE(Decoration_YellowBall_M);/*1�x�ǂݍ��ނ��ƂŌy�ʉ�*/

	srand(timeGetTime());
	GameNorm.Create();
	GetEnemyManager.Create();
	loadStageData = new LoadStageData(StageNo);
	ground = new Ground;
	
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	GetPlayerCam.Create();
	

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


	loadStageData->SetStageMap(*mapObjManager, GameNorm, *gameObjective, *stageBorder);
	
	//-------------------------------------------------------
	GetPlayerCam.SetPos(&D3DXVECTOR3(stageBorder->Right / 2, 0, 10.0f));				//�v���C���[�̏����ʒu

	stage1Enclosure = new Stage1Enclosure(stageBorder);


	//-----------------------------
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);


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

	Direct3D::GetInstance().GetD3DDevice()->SetLight(0, &Light);
	Direct3D::GetInstance().GetD3DDevice()->LightEnable(0, TRUE);
	//-----------------------------
	BeginScene();
}

GameScene::~GameScene()
{
	delete loadStageData;
	delete ground;
	delete skyBox;
	delete stage1Enclosure;
	GameNorm.Destroy();
	delete snowBallManager;
	delete mapObjManager;
	GetPlayerCam.Destroy();

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
	if (nowState== IN_RESULT)
	{
		return;		//�`�悵�Ȃ�		(�C���X�^���X���폜������������񂾂낤���H)��
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	if (nowState == IN_GAME)
	{
		GetEnemyManager.Draw();
		EnemyAnime.Draw();
		snowBallManager->Draw();
		Effect.Draw();

		GetPlayer.Draw();		//��Z�o�b�t�@�N���A�����Ă��邽�ߍŌ�ɕ`�悷��
	}
}

void GameScene::SetCamera(void)
{
	if (nowState == IN_RESULT)
	{
		resultCam->SetCamera();				//���U���g���̃J����
		return;
	}

	if (nowState == IN_GAME)
	{
		GetPlayerCam.SetCamera();
	}

}

void GameScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	Sprite::GetInstance().GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	if (nowState == IN_GAME)		//���U���g�\�����͏���
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
	if (nowState == IN_RESULT)
	{
		RECT RcResult = { 0, 0, 820, 160 };
		Sprite::GetInstance().GetSprite()->SetTransform(&resultMat);
		Sprite::GetInstance().GetSprite()->Draw(resultTex, &RcResult, &D3DXVECTOR3(820 / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT RcReturn = { 0, 0, 499, 84 };
		if (ResulCnt <= 0)
		{
			Sprite::GetInstance().GetSprite()->SetTransform(&returnMat);
			Sprite::GetInstance().GetSprite()->Draw(returnTex, &RcReturn, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	GetBackToTitle.Draw();
	GetSceneSwitchEffect.Draw();			//��ɕ`��

	// �`��I��
	Sprite::GetInstance().GetSprite()->End();
}

bool GameScene::Update()
{
	//-------------------------------------------------------------------
	//�^�C�g���ɖ߂�O�̊m�F		����̃��W���[���ɂ���
	//-------------------------------------------------------------------
	if (BackToTitle() == true)return true;		//���쒆�͑������^�[��


	//------------------------------------------------------
	//�Ƃ肠��������
	//------------------------------------------------------
	switch (nowState)
	{
	case IN_GAME:
		break;
	case SWITCH_RESULT:

		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			BeginResult();
		}
		return true;
		break;

	case IN_RESULT:
		ResultUpdate();
		break;

	case END_RESULT:
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			GetSceneSwitcher.SwitchScene(new MenuScene());
			GetSound.Stop(InGameBGM_Sound);
			return false;
		}
		return true;
		break;

	case TIME_UP_EFFECT:
		break;

	case BACK_TO_TITLE_GAME:
		if (GetSceneSwitchEffect.GetFadeState() == STOP)		//�V�[���J�ڂ��I����Ă�����ڍs
		{
			GetSceneSwitcher.SwitchScene(new TitleScene());			//�^�C�g���ֈڍs
			return false;
		}
		return true;
		break;

	default:
		break;
	}

	if (addUpdate != nullptr)
	{
		GameSceneState NextState;
		NextState = addUpdate->AddUpdate();

		if (NextState != nowState)
		{
			delete addUpdate;
			addUpdate = nullptr;

			switch (NextState)
			{
			case IN_GAME:
				break;
			case SWITCH_RESULT:		//���U���g�ڍs
				SwitchResult();
				break;
			case IN_RESULT:			//���U���g���̏���
				BeginResult();
				break;
			case END_RESULT:
				
				break;
			case TIME_UP_EFFECT:	//�I�����̉��o�Đ�
				BeginTimeUpEffect();
				break;
			default:
				break;
			}
		}
	}

	//------------------------------------------------------
	//�Ƃ肠�������������܂�
	//------------------------------------------------------

	Collision();

	//----------------------------------------------------------------------------------------------------------------
	//�v���C���[�̍X�V	���J�����������蔻�聨�v���C���[�̏��Ԃ�	�v���C���[�̂̈ʒu���J�����Ƃ���邽��
	//----------------------------------------------------------------------------------------------------------------
	GetPlayerCam.Update(*stageBorder);						//�v���C���[�J�����̈ړ�

	//�}�b�v�I�u�W�F�ƃv���C���[�̓����蔻��
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		CollisionObserver::PlayertoObj(&GetPlayerCam, mapObjManager->mapObj[i]);
	}

	GetPlayer.Update(*pickUpInstructions, this);		//�J�������X�V���Ă���

	AddSnowBallUI::GetInstance().Update();
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &GetPlayerCam.GetmView());		//�J�����̃A�b�v�f�[�g�̌�ɌĂ�

	GetEnemyManager.Update(this);

	remainingBallUI->SetRemainingBallCnt(GetPlayer.GetRemainingBalls());
	snowBallManager->Update();

	Effect.SetBillBoardMat(&TmpBillBoardMat);		//��effectManager��Update�̑O�ɌĂ�
	Effect.Update();
	EnemyAnime.Updata();

	GetDecorationManager.Updata();

	

	//--------------------------------------------------------
	//HitEffect
	//--------------------------------------------------------

	for (auto PlayerHitEffect_Right : playerHitEffect_Right)
	{
		PlayerHitEffect_Right->Update();
	}

	for (auto PlayerHitEffect_Left : playerHitEffect_Left)
	{
		PlayerHitEffect_Left->Update();
	}

	playerHitEffect_Back->Update();

	GetSpawnerManager.Update(*stageBorder);

	//----------------------------------------------------------------------------------------
	//���ԏ���
	//----------------------------------------------------------------------------------------
	for (unsigned int i = 0; i < timePenaltyUI.size(); i++)
	{
		if (timePenaltyUI[i]->Update() == false)
		{
			delete timePenaltyUI[i];
			timePenaltyUI.erase(timePenaltyUI.begin() + i);
			i--;
		}
	}
	//timeUI->SetTime_s(GameNormManager->GetRemainingTime_s());		//�t���[����b�ɒ����ēn���Ă���
	timeUI->SetTime_s(GameTime::GetRemainingTime_s());		//�t���[����b�ɒ����ēn���Ă���
	timeUI->Update();

	//----------------------------------------------------------------------------------------
	//�m���}����
	//----------------------------------------------------------------------------------------
	bool NormState;
	NormState = GameNorm.GetNormState();
	if (NormState == false)
	{
		gameObjective->SetNowNormCnt(GameNorm.GetNowNormCnt());		//���݂̐���n��
	}
	else
	{
		gameObjective->SetNormState(GameNorm.GetNormState());			//���݂̃m���}�󋵂�n��		//�����P�̗]�n����
	}

	return true;
}

SnowBallManager& GameScene::GetSnowBallManager()
{
	return *snowBallManager;
}

StageBorder& GameScene::GetStageBorder()
{
	return *stageBorder;
}

void GameScene::BeginScene()
{
	nowState = IN_GAME;
	addUpdate = new GameTime();
	GetSound.Play2D(InGameBGM_Sound);
	GetSceneSwitchEffect.PlayFadeIn();
}

void GameScene::EndScene()
{
	nowState = BACK_TO_TITLE_GAME;
	GetSceneSwitchEffect.PlayFadeOut();
	GetSound.Stop(InGameBGM_Sound);										//�T�E���h���Đ���~
	GetSound.Stop(Clock_Sound);										//�T�E���h���Đ���~(�ڍs���Ɏ~�߂�T�E���h���܂Ƃ߂��֐��쐬)
}

void GameScene::Collision()
{
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
					//HeadShoot�p�T�E���h�Đ�
					//-------------------------------------------------------------
					GetSound.Play2D(HeadShoot_Sound);
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

				GetSound.Play2D(Damage_Sound);

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
			if (CollisionObserver::SnowBalltoObj(snowBallManager->snowBall[sj], mapObjManager->mapObj[mi]))		//������true���Ԃ��Ă���
			{
				//SnowFrag�G�t�F�N�g�Ă�
				Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

				//�T�E���h
				GetSound.Play2D(SnowBallBreak_Sound);

				//���񂾃C���X�^���X�폜
				snowBallManager->DeleteInstance(sj);
				sj--;
			}
	}

	//�G�̐�ʂƃv���C���[�̂����蔻��
	for (unsigned int si = 0; si < snowBallManager->snowBall.size(); si++)
	{
		if (CollisionObserver::EnemySnowBalltoPlayer(&GetPlayer, snowBallManager->snowBall[si]))
		{
			//SnowFrag�G�t�F�N�g�Ă�
			Effect.NewSnowFrag(snowBallManager->snowBall[si]->GetPos());

			//�T�E���h
			GetSound.Play2D(Damage_Sound);

			//GameNormManager->PlayerTakeDamage();			//HIT���̃��\�b�h���Ă�
			GameTime::PlayerTakeDamage(3);
			timePenaltyUI.push_back(new TimePenaltyUI(3));		//�ϐ���

			//----------------------------------------------------
			//HitEffecct�̏���(Effect�̃N���X�ɕϐ��������������������̂ł́H)
			//----------------------------------------------------
			HitEffectID ActivationID;

			ActivationID = PlayerHitEffect::CalculateHitDirection(snowBallManager->snowBall[si]->GetMoveVec());

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
				for (auto PlayerHitEffect_Left : playerHitEffect_Left)
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

			snowBallManager->DeleteInstance(si);
			si--;						//���������l�߂�
		}
	}

	//�f�R���[�V������MapObj�̓����蔻��
	for (unsigned int i = 0; i < GetDecorationManager.decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(GetDecorationManager.decoration[i], mapObjManager->mapObj[j]);
		}
	}

	//�G��MapObj�̔���
	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int mj = 0; mj < mapObjManager->mapObj.size(); mj++)
		{
			CollisionObserver::EnemyToMapObj(GetEnemyManager.enemy[ei], mapObjManager->mapObj[mj]);
		}
	}
}

void GameScene::SwitchResult()
{
	nowState = SWITCH_RESULT;
	GetSceneSwitchEffect.PlayFadeOut();
}

void GameScene::BeginResult(void)
{
	nowState = IN_RESULT;
	//�G��G�t�F�N�g�Ȃǎז��Ȃ��̂��폜����
	GetEnemyManager.AllDelete();
	Effect.AllDelete();
	snowBallManager->AllDelete();
	GetDecorationManager.DeleteToResult();

	GetSceneSwitchEffect.PlayFadeIn();
	resultCam = new ResultCam();
}

void GameScene::EndResult(void)
{
	nowState = END_RESULT;
	GetSceneSwitchEffect.PlayFadeOut();
}

//���̕ӂ�̓��t�@�N�^�����O�̕K�v����
bool GameScene::ResultUpdate(void)
{
	resultCam->Update(&mapObjManager->GetXmasTreePos());

	ResulCnt--;

	if (ResulCnt <= 0)//��莞�ԓ��͂��������Ȃ�
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//�E�N���b�N���������ƃV�[���J��
		{
			GetSound.Play2D(Success_Sound);
			EndResult();
		}
	}
	return true;
}

bool GameScene::BackToTitle(void)
{
	RETURN_STATE GameSceneState;
	GameSceneState = GetBackToTitle.CallBackToTitle();

	if (GameSceneState == WAITING_INPUT)return true;
	if (GameSceneState == RETURN_TITLE)
	{
		EndScene();
		return false;
	}

	if (GameSceneState == NOT_ACTIVE)return false;
	if (GameSceneState == CANCEL)
	{
		PlayerStateIdle::LimitKeepPushShootKey();
		return false;			//��������J�������ړ�����̂����Ƃ�����
	}
	
	return false;
}

void GameScene::BeginTimeUpEffect()
{
	nowState = TIME_UP_EFFECT;
	GetSound.Stop(Clock_Sound);
	GetSound.Play2D(EndWhistle_Sound);
	addUpdate = new TimeUpEffect();
}
