#pragma once
#include"main.h"
#include<string>
#include<map>

//------------------------------------------------------------------------------------------------
//※シングルトンクラス
//マクロ定義でGetResourceがインスタンス参照になっている
//XFILEとスプライトを管理するクラス
//------------------------------------------------------------------------------------------------

#define GetResource ResourceManager::GetInstance()

class ResourceManager
{
public:
	static void Create();
	static void Destroy();

	//ファイル名を指定
	XFILE			  GetXFILE(std::string FileName);

	//ファイル名を指定,  横幅,   高さ,  カラーキー
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);

	static ResourceManager& GetInstance();

	~ResourceManager();
private:
	ResourceManager();
	
	static ResourceManager *resourceManager;

	std::map<std::string, XFILE> XFILEList;				//ポインタ型で宣言するように変える		ポインタ型で宣言した場合そのポインタ変数の削除が必要
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);
};
