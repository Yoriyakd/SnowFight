#include "BackToTitle.h"
#include"../TitleScene/TitleScene.h"
#include"../DirectX/Sprite.h"

const D3DXVECTOR3 BackToTitle::DISPLAY_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const D3DXVECTOR2 BackToTitle::YESBUTTON_POS = D3DXVECTOR2(440.0f, 300.0f);
const D3DXVECTOR2 BackToTitle::NOBUTTON_POS = D3DXVECTOR2(740.0f, 300.0f);
const D3DXVECTOR2 BackToTitle::BUTTON_HIT_AREA = D3DXVECTOR2(132.0f, 132.0f);
const RECT BackToTitle::BACK_RECT = RECT{ 0, 0, 1280, 720 };

BackToTitle::BackToTitle() : nowState(false)
{
	tex = GetResource.GetTexture(BackToTitle_Tex);
	D3DXMatrixTranslation(&mat, DISPLAY_POS.x, DISPLAY_POS.y, DISPLAY_POS.z);

	YesButton = new BackToTitleButton();

	ButtonData TmpData;
	TmpData.Pos = YESBUTTON_POS;
	TmpData.BoxSize = BUTTON_HIT_AREA;

	YesButton->Initialize(TmpData, GetResource.GetTexture(YesButton_Tex));		//CSVから読み込むように変更する☆
	
	NoButton = new BackToTitleButton();

	TmpData.Pos = NOBUTTON_POS;
	

	NoButton->Initialize(TmpData, GetResource.GetTexture(NoButton_Tex));
}

BackToTitle::~BackToTitle()
{
}

void BackToTitle::Draw()
{
	if (nowState == true)		//タイトルバック確認画面が呼ばれている間のみ描画
	{
		Sprite::GetInstance().GetSprite()->SetTransform(&mat);
		Sprite::GetInstance().GetSprite()->Draw(tex, &BACK_RECT, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		YesButton->Draw();
		NoButton->Draw();

		GetCursor.Draw();
	}
}

RETURN_STATE BackToTitle::CallBackToTitle()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (isESCKey == true)
		{
			if (nowState == true)
			{
				//カーソル
				GetCursor.ShowCursor(false);

				nowState = false;
				isESCKey = false;	//ESCを連続して押せないように
				return CANCEL;
			}
			else
			{
				GetCursor.ShowCursor(true);
				nowState = true;
				isESCKey = false;	//実行ESCを連続して押せないように
			}
		}
	}
	else
	{
		isESCKey = true;
	}
	
	if (nowState == false)return NOT_ACTIVE;

	YesButton->Update();
	NoButton->Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (YesButton->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			nowState = false;
			GetCursor.ShowCursor(false);

			nowState = false;

			return RETURN_TITLE;
		}
		if (NoButton->GetState() == true) 
		{
			nowState = false;
			GetCursor.ShowCursor(false);
			nowState = false;
			return CANCEL;
		}
	}

	return WAITING_INPUT;
}
