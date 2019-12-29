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
	ArmL_M,
	ArmR_M,
	Bench_M,
	BenchCollision_M,
	Bobbin_Red_M,
	Decoration_RedBall_M,
	Decoration_BlueBall_M,
	Decoration_YellowBall_M,
	EnemyBody_M,
	EnemyHat_M,
	Kamakura_M,
	Shoes_M,
	SnowBall_M,
	Sky_M,
	Tree_M,
	XmasTree_M
};

enum TexName
{

};

class ResourceManager : public SingletonBase<ResourceManager>
{
public:
	friend class SingletonBase<ResourceManager>;			//SingletonBaseでのインスタンス作成削除は許可

	//enumで定義されたMeshNameを入れる
	XFILE			  GetXFILE(enum MeshName);

	//ファイル名を指定,  横幅,   高さ,  カラーキー
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
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
		{Bench_M,                 "Bench.x"},
		{BenchCollision_M,        "BenchCollision.x"},
		{Bobbin_Red_M,            "Bobbin_Red.x"},
		{Decoration_RedBall_M,    "Decoration_RedBall.x"},
		{Decoration_BlueBall_M,   "Decoration_BlueBall.x"},
		{Decoration_YellowBall_M, "Decoration_YellowBall.x"},
		{EnemyBody_M,             "EnemyBody.x"},
		{EnemyHat_M,              "EnemyHat.x"},
		{Kamakura_M,              "Kamakura.x"},
		{Shoes_M,                 "Shoes.x"},
		{SnowBall_M,              "SnowBall.x"},
		{Sky_M,                   "Sky.x"},
		{Tree_M,                  "Tree.x"},
		{XmasTree_M,              "XmasTree.x"}
	};
};

ResourceManager* SingletonBase<ResourceManager>::instance = nullptr;		//nullptrで初期化(DirectXの機能を使うためDirectX初期化後に作成する必要がある)staticで最初に確保されていたやつはどこへ...?解放されてないきがするぞ

