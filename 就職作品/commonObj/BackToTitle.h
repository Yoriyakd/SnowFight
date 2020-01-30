#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"ButtonBase.h"
#include"../SceanSwitcher/SceneSwitcher.h"

//--------------------------------------------------------------
//タイトルバック確認画面のクラス
//CallBackToTitleメソッドを呼び戻り値がfalseならシーンが切り替わる(※呼び出し側のUpdateでfalseを返すことをわすれないように)
//※シングルトン
//--------------------------------------------------------------

#define GetBackToTitle BackToTitle::GetInstance()
class BackToTitle : public SingletonBase<BackToTitle> {
	friend class SingletonBase<ResourceManager>;			//SingletonBaseでのインスタンス作成削除は許可
public:
	BackToTitle();
	~BackToTitle();

	void Draw();
	int CallBackToTitle();		//戻り値　-1 = No, 0 = 選択なし画面継続 1 = Yes シーン切り替え

	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;

	bool calledState;			//呼び出されているかを表す

	ButtonBase *YesButton;
	ButtonBase *NoButton;
};

BackToTitle* SingletonBase<BackToTitle>::instance = nullptr;		//nullptrで初期化