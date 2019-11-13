
#include "GameScene.h"

EnemyManager *enemyManager;
Player *player;
D3DLIGHT9 Light;
StageBorder stageBorder;
const float StageBorderOffsetX = 15.0f;			//�O���܂ł̋���
const float StageBorderOffsetZ = 15.0f;			//�O���܂ł̋���
const float Gravity = -0.05f;						//�d��	���K�����̒l�̂���

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	setEnemies = new SetEnemies();
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	collisionObserver = new CollisionObserver();
	playerCam = new PlayerCamera(SCRW, SCRH, hwnd);

	int FenceCntX = 15, FenceCntY = 15;		//�����I�ɋ��߂���悤�ɂ���		���������t�F���X�ȊO��ݒu���遙

	loadStageData->GetStageSize(&stageSizeX, &stageSizeZ);

	//-------------------------------------------------------
	//�X�e�[�W�̋��E�����߂�
	//-------------------------------------------------------
	stageBorder.Top = stageSizeZ + StageBorderOffsetZ;
	stageBorder.Bottom = -1 * StageBorderOffsetZ;
	stageBorder.Left = -1 * StageBorderOffsetX;
	stageBorder.Right = stageSizeX + StageBorderOffsetX;
	//-------------------------------------------------------

	fenceManager = new FenceManager(FenceCntX, FenceCntY, StageBorderOffsetX, StageBorderOffsetZ);		//�X�e�[�W�̋��E�f�[�^�����炤�悤�ύX����
	fenceManager->SetStageSize(stageSizeX, stageSizeZ);
	fenceManager->SetFence();		//�t�F���X��z�u

	playerCam->SetStageBorder(stageBorder);		//�X�e�[�W�̋��E�f�[�^���Z�b�g
	player->SetPlayerCamPointer(playerCam);		//�v���C���[�J�����̃|�C���^���Z�b�g
	effectManager->SetPlayerCamPointer(playerCam);	//�v���C���[�J�����̃|�C���^���Z�b�g
	setEnemies->SetStageSize(stageSizeX, stageSizeZ);
	
	mapObjManager->SetTree(D3DXVECTOR3(50, 0, 50));		//test ��
	mapObjManager->SetBench(D3DXVECTOR3(30, 0, 80));		//test�@��

	for (int i = 0; i <  loadStageData->GetEnemyNum(); i++)
	{
		enemyManager->SetEnemy(loadStageData->GetEnemyData(i));			//enemyManager���C���X�^���X���쐬����
	}

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
	delete fenceManager;
	delete snowBallManager;
	delete mapObjManager;
	delete collisionObserver;
}

void GameScene::Render3D(void)
{
	skyBox->Draw();
	ground->Draw();
	fenceManager->Draw();
	mapObjManager->Draw();
	enemyManager->Draw();
	player->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
}

void GameScene::SetCamera(void)
{
	playerCam->SetCamera();
}

void GameScene::Render2D(void)
{
}

bool GameScene::Update()
{
	if (GetAsyncKeyState('P') & 0x8000)		//������ς��Ė{������
	{
		setEnemies->SetEnemy();
	}
	enemyManager->Update(snowBallManager);
	playerCam->Update();
	player->Update(snowBallManager);		//�J�������X�V���Ă���
	snowBallManager->Update();
	effectManager->Update();

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	collisionObserver->SnowBalltoObj(snowBallManager, mapObjManager);
	collisionObserver->PlayertoObj(playerCam, mapObjManager);
	return true;
}
