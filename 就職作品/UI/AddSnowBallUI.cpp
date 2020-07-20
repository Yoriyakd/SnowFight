#include "AddSnowBallUI.h"
#include"../DirectX/Sprite.h"

const RECT AddSnowBallUI::Rc = { 0, 0, 158, 61 };
const D3DXVECTOR3 AddSnowBallUI::DISPLAY_POS = D3DXVECTOR3(700, 450, 0);
const int AddSnowBallUI::FADE_OUT_SPEED = 10;
const float AddSnowBallUI::MOVE_SPPE_Y = -2;

AddSnowBallUI::AddSnowBallUI()
{
	tex = GetResource.GetTexture(AddSnowBall_Tex);
}

AddSnowBallUI::~AddSnowBallUI()
{
}

void AddSnowBallUI::AddSnowBall()
{
	D3DXMATRIX TmpMat;

	D3DXMatrixTranslation(&TmpMat, DISPLAY_POS.x, DISPLAY_POS.y, DISPLAY_POS.z);
	AddUI.push_back(new AddSnowBallData{TmpMat, D3DCOLLARMaxARGBValue::a});
}

void AddSnowBallUI::Draw()
{
	for (unsigned int i = 0; i < AddUI.size(); i++)
	{
		Sprite::GetInstance().GetSprite()->SetTransform(&AddUI[i]->mat);
		Sprite::GetInstance().GetSprite()->Draw(tex, &Rc, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(AddUI[i]->alpha, D3DCOLLARMaxARGBValue::r, D3DCOLLARMaxARGBValue::g, D3DCOLLARMaxARGBValue::b));
	}
}

void AddSnowBallUI::Update()
{
	for (unsigned int i = 0; i < AddUI.size(); i++)
	{
		AddUI[i]->alpha -= FADE_OUT_SPEED;

		D3DXMATRIX TmpMat;

		D3DXMatrixTranslation(&TmpMat, 0, MOVE_SPPE_Y, 0);
		AddUI[i]->mat *= TmpMat;

		if (AddUI[i]->alpha < 0)
		{
			delete AddUI[i];
			AddUI.erase(AddUI.begin() + i);
			i--;		//Á‚µ‚½•ª‹l‚ß‚é
		}
	}
}
