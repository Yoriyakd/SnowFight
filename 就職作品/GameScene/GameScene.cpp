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
	playerCam = new PlayerCamera(SCRW, SCRH, hwnd);
	eventManager = new EventManager();
	decorationManager = new DecorationManager();
	pickUpInstructions = new PickUpInstructions();


	decorationManager->decoration.push_back(new Decoration_Ball(&D3DXVECTOR3(80, 0, 50), RED_BALL));		//test��

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
	stageBorder->Right = StageSizeX ;
	//-------------------------------------------------------
	playerCam->SetPos(&D3DXVECTOR3(StageSizeX / 2, 0, 10.0f));				//�v���C���[�̏����ʒu

	//fenceManager = new FenceManager(FenceCntX, FenceCntY, stageSizeX, stageSizeZ);		//�X�e�[�W�̋��E�f�[�^�����炤�悤�ύX����
	//fenceManager->SetStageSize(stageSizeX, stageSizeZ);
	//fenceManager->SetFence();		//�t�F���X��z�u

	player->SetPlayerCamPointer(playerCam);		//�v���C���[�J�����̃|�C���^���Z�b�g
	effectManager->SetPlayerCamPointer(playerCam);	//�v���C���[�J�����̃|�C���^���Z�b�g
	
	//-----------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	Light.Diffuse.a = 1.0f;
	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

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
	//delete fenceManager;
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
	//fenceManager->Draw();
	mapObjManager->Draw();
	enemyManager->Draw();
	player->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
	decorationManager->Draw();
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
	// �`��I��
	lpSprite->End();
}

bool GameScene::Update()
{
	enemyManager->Update(snowBallManager);
	playerCam->Update();
	player->Update(snowBallManager);		//�J�������X�V���Ă���
	snowBallManager->Update();
	effectManager->Update();
	eventManager->Update();
	decorationManager->Updata();

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	collisionObserver->SnowBalltoObj(snowBallManager, mapObjManager);
	collisionObserver->PlayertoObj(playerCam, mapObjManager);
	return true;
}
