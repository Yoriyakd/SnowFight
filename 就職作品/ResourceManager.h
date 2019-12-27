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

class ResourceManager : public SingletonBase<ResourceManager>
{
public:
	friend class SingletonBase<ResourceManager>;			//SingletonBaseでのインスタンス作成削除は許可

	//ファイル名を指定
	XFILE			  GetXFILE(std::string FileName);

	//ファイル名を指定,  横幅,   高さ,  カラーキー
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
protected:

private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, XFILE> XFILEList;				//ポインタ型で宣言するように変える		ポインタ型で宣言した場合そのポインタ変数の削除が必要
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);
};

ResourceManager* SingletonBase<ResourceManager>::instance = nullptr;		//nullptrで初期化(DirectXの機能を使うためDirectX初期化後に作成する必要がある)staticで最初に確保されていたやつはどこへ...?解放されてないきがするぞ