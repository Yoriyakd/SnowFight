#include "AddSnowBallUI.h"

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

	D3DXMatrixTranslation(&TmpMat, 700, 450, 0);
	AddUI.push_back(new AddSnowBallData{TmpMat, 255});
}

void AddSnowBallUI::Draw()
{
	RECT Rc = { 0, 0, 158, 61 };
	for (unsigned int i = 0; i < AddUI.size(); i++)
	{
		lpSprite->SetTransform(&AddUI[i]->mat);
		lpSprite->Draw(tex, &Rc, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(AddUI[i]->alpha, 255, 255, 255));
	}
}

void AddSnowBallUI::Update()
{
	for (unsigned int i = 0; i < AddUI.size(); i++)
	{
		AddUI[i]->alpha -= 10;

		D3DXMATRIX TmpMat;

		D3DXMatrixTranslation(&TmpMat, 0, -2, 0);
		AddUI[i]->mat *= TmpMat;

		if (AddUI[i]->alpha < 0)
		{
			delete AddUI[i];
			AddUI.erase(AddUI.begin() + i);
			i--;		//Á‚µ‚½•ª‹l‚ß‚é
		}
	}
}
