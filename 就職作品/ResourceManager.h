#pragma once
#include"main.h"
#include<string>
#include<map>
#include"SingletonBase.h"

//------------------------------------------------------------------------------------------------
//※シングルトンクラス
//マクロ定義でGetResourceがインスタンス参照になっている
//XFILEとスプライトを管理するクラス
//------------------------------------------------------------------------------------------------

#define GetResource ResourceManager::GetInstance()

enum MeshName
{
//playerMesh
	ArmL_M,
	ArmR_M,
	Shoes_M,

//Enemy
	EnemyBody_M,
	EnemyHand_M,
	EnemyHat_M,

//MapObject
	Bench_M,
	BenchCollision_M,
	Bobbin_Red_M,
	Kamakura_M,
	Tree_M,
	XmasTree_M,

//Decoration
	Decoration_RedBall_M,
	Decoration_BlueBall_M,
	Decoration_YellowBall_M,
	
	SnowBall_M,
	Sky_M,
};

struct TexData {
	char FileName[64];		//ファイル名は63文字まで
	int Width;
	int Hight;
	D3DCOLOR Color;
};

enum TexName
{
//Title
	TitleBack_Tex,
	TitleLogo_Tex,
	TitleInstructions_Tex,

//MenuScene
	MenuBack_Tex,
	MenuBoard_Tex,
	MenuCursor_Tex,
	MenuHeadChar_Tex,
	ButtonText_Tex,
	ButtonBack_Tex,
	ButtonNum_Tex,
	Stage1Button_Tex,
	Stage2Button_Tex,

//InGame-----------------------------
	ThrowGhostSnow_Tex,
	ThrowGhostDeco_Tex,
	PickUpInstructions_Tex,

//Result
	ResultHead_Tex,
	ResultReturn_Tex,

//UI
	GameUINumber_Tex,
	RemainingBallBack_Tex,
	TimeLogo_Tex,
	TimeNumber_Tex,
	TimePenalty_Tex,
	GameObjectiveBack_Tex,
	GameObjectiveClear_Tex,

//Effect
	SnowLocus_Tex,
	SnowFrag_Tex,
	SnowSmoke_Tex,
	SceneSwitch_Tex,
	HitEffect_Tex,
	BackHitEffect_Tex,

//Map
	Brick_Tex,
	Hedge_Tex,
	Pole_Tex,
	Ground_Tex,
};

class ResourceManager : public SingletonBase<ResourceManager>
{
public:
	friend class SingletonBase<ResourceManager>;			//SingletonBaseでのインスタンス作成削除は許可

	//enumで定義されたMeshNameを入れる
	XFILE			  GetXFILE(enum MeshName);

	//ファイル名を指定,  横幅,   高さ,  カラーキー
	LPDIRECT3DTEXTURE9 GetTexture(enum TexName);
protected:

private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, XFILE> XFILEList;				//ポインタ型で宣言するように変える		ポインタ型で宣言した場合そのポインタ変数の削除が必要
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);

	std::map<MeshName, std::string> MeshFileName{
		{ArmL_M,                  "ArmL.x"},
		{ArmR_M,                  "ArmR.x"},
		{Shoes_M,                 "Shoes.x"},

		{EnemyBody_M,             "EnemyBody.x"},
		{EnemyHand_M,             "EnemyHand.x"},
		{EnemyHat_M,              "EnemyHat.x"},

		{Bench_M,                 "Bench.x"},
		{BenchCollision_M,        "BenchCollision.x"},
		{Bobbin_Red_M,            "Bobbin_Red.x"},
		{Kamakura_M,              "Kamakura.x"},
		{Tree_M,                  "Tree.x"},
		{XmasTree_M,              "XmasTree.x"},

		{Decoration_RedBall_M,    "Decoration_RedBall.x"},
		{Decoration_BlueBall_M,   "Decoration_BlueBall.x"},
		{Decoration_YellowBall_M, "Decoration_YellowBall.x"},

		{SnowBall_M,              "SnowBall.x"},
		{Sky_M,                   "Sky.x"},
	};

	std::map<TexName, TexData> TexFileName{
		//Title
		{TitleBack_Tex,           TexData{"BackTex.jpg", 1280, 720, NULL}},
		{TitleLogo_Tex,           TexData{"TitleLogo.png", 832, 170, NULL}},
		{TitleInstructions_Tex,   TexData{"TitleInstructions.png", 426, 116, NULL}},

		//MenuScene
		{MenuBack_Tex,            TexData{"Menuback.jpeg", 1280, 720, NULL}},
		{MenuBoard_Tex,           TexData{"StageSelect_Board.png", 768, 540, NULL}},
		{MenuCursor_Tex,          TexData{"Cursor.png", 64, 64, NULL}},
		{MenuHeadChar_Tex,        TexData{"StageSelect_Menu.png", 640, 64, NULL}},
		{ButtonText_Tex,		  TexData{"StageSelectText.png", 132, 30, NULL}},
		{ButtonBack_Tex,		  TexData{"StageButton.jpg", 132, 132, NULL}},
		{ButtonNum_Tex,			  TexData{"StageSelectNum.png", 300, 30, NULL}},
		{Stage1Button_Tex,        TexData{"Stage1Pic.png", 96, 54, NULL}},
		{Stage2Button_Tex,        TexData{"Stage1Pic.png", 96, 54, NULL}},

		//InGame
		{ThrowGhostSnow_Tex,      TexData{"PredictionLine_Snow.png", 64, 64, NULL}},
		{ThrowGhostDeco_Tex,      TexData{"PredictionLine_Deco.png", 64, 64, NULL}},
		{PickUpInstructions_Tex,  TexData{"PickUpInstructions.png", 256, 64, NULL}},

		//Result
		{ResultHead_Tex,          TexData{"Result.png", 820, 160, NULL}},
		{ResultReturn_Tex,        TexData{"Click_To_Return.png", 420, 40, NULL}},

		//UI
		{GameUINumber_Tex,		  TexData{"Number.png", 420, 42, NULL}},
		{RemainingBallBack_Tex,   TexData{"SnowBallUI.png", 256, 64, NULL}},
		{TimeLogo_Tex,            TexData{"TimeLogo.png", 194, 46, NULL}},
		{TimeNumber_Tex,          TexData{"Number_Time.png", 460, 50, NULL}},
		{TimePenalty_Tex,         TexData{"Minus.png", 46, 46, NULL}},
		{GameObjectiveBack_Tex,   TexData{"GameObjective.png", 400, 64, NULL}},
		{GameObjectiveClear_Tex,  TexData{"Clear.png", 400, 64, NULL}},

		//Effect
		{SnowLocus_Tex,           TexData{"FallingSnow.png", 250, 250, NULL}},
		{SnowFrag_Tex,            TexData{"SnowFrag.png", 1024, 1024, NULL}},
		{SnowSmoke_Tex,           TexData{"Smoke.png", 250, 250, NULL}},			//もっと煙のテクスチャに変える
		{SceneSwitch_Tex,         TexData{"SceneSwitchEffect.png", 32, 32, NULL}},
		{HitEffect_Tex,           TexData{"HitEffect.png", 500, 500, NULL}},
		{BackHitEffect_Tex,       TexData{"BackHitEffect.png", 1280, 720, NULL}},

		//Map
		{Brick_Tex,               TexData{"Brick.jpg", 512, 512, NULL}},
		{Hedge_Tex,               TexData{"Hedge.png", 512, 512, NULL}},
		{Pole_Tex,                TexData{"Pole.png", 512, 512, NULL}},
		{Ground_Tex,              TexData{"SnowGround.png", 512, 512, NULL}},
	};
};
ResourceManager* SingletonBase<ResourceManager>::instance = nullptr;		//nullptrで初期化(DirectXの機能を使うためDirectX初期化後に作成する必要がある)staticで最初に確保されていたやつはどこへ...?解放されてないきがするぞ