#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"BackToTitleButton.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../Sound/SoundManager.h"

//--------------------------------------------------------------
//タイトルバック確認画面のクラス
//CallBackToTitleメソッドを呼び戻り値がfalseならシーンが切り替わる(※呼び出し側のUpdateでfalseを返すことをわすれないように)
//※シングルトン
//--------------------------------------------------------------

enum RETURN_STATE { RETURN_TITLE, CANCEL, WAITING_INPUT, NOT_ACTIVE };

#define GetBackToTitle BackToTitle::GetInstance()
class BackToTitle : public SingletonBase<BackToTitle> {
	friend class SingletonBase<ResourceManager>;			//SingletonBaseでのインスタンス作成削除は許可
public:
	BackToTitle();
	~BackToTitle();

	void Draw();
	RETURN_STATE CallBackToTitle();		//戻り値　-1 = No, 0 = 選択なし画面継続 1 = Yes シーン切り替え

	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;

	bool nowState;			//呼び出されているかを表す
	bool isESCKey;

	BackToTitleButton *YesButton;
	BackToTitleButton *NoButton;
};

//class ESCUpdateBase {
//
//};

BackToTitle* SingletonBase<BackToTitle>::instance = nullptr;		//nullptrで初期化