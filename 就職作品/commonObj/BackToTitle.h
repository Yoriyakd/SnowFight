#pragma once
#include"../SingletonBase.h"
#include"../ResourceManager.h"
#include"BackToTitleButton.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../Sound/SoundManager.h"
#include"../commonObj/Cursor.h"

//--------------------------------------------------------------
//タイトルバック確認画面のクラス
//CallBackToTitleメソッドを呼び戻り値がfalseならシーンが切り替わる(※呼び出し側のUpdateでfalseを返すことをわすれないように)
//※シングルトン
//--------------------------------------------------------------

enum RETURN_STATE { RETURN_TITLE, CANCEL, WAITING_INPUT, NOT_ACTIVE };

#define GetBackToTitle BackToTitle::GetInstance()
class BackToTitle : public SingletonBase<BackToTitle> {
	friend class SingletonBase<BackToTitle>;			//SingletonBaseでのインスタンス作成削除は許可
public:

	void Draw();
	RETURN_STATE CallBackToTitle();		//戻り値　-1 = No, 0 = 選択なし画面継続 1 = Yes シーン切り替え

private:
	LPDIRECT3DTEXTURE9 tex;
	D3DXMATRIX mat;
	static const D3DXVECTOR3 DISPLAY_POS;
	const static RECT BACK_RECT;

	bool nowState;			//呼び出されているかを表す
	bool isESCKey;

	BackToTitleButton *YesButton;
	static const D3DXVECTOR2 YESBUTTON_POS;

	BackToTitleButton *NoButton;
	static const D3DXVECTOR2 NOBUTTON_POS;

	static const D3DXVECTOR2 BUTTON_HIT_AREA;
	BackToTitle();
	~BackToTitle();
};