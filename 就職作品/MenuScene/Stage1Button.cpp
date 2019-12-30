#include "Stage1Button.h"

Stage1Button::Stage1Button()
{
	tex = GetResource.GetTexture(Button_Tex);
	pos = D3DXVECTOR2(480, 190);
	texSize = D3DXVECTOR2(132, 132);
	boxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
}

Stage1Button::~Stage1Button()
{
}
