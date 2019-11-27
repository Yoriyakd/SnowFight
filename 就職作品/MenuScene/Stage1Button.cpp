#include "Stage1Button.h"

Stage1Button::Stage1Button()
{
	tex = resourceManager->GetTexture("Stage1.jpeg", 132, 132, NULL);
	pos = D3DXVECTOR2(480, 190);
	texSize = D3DXVECTOR2(132, 132);
	boxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
}

Stage1Button::~Stage1Button()
{
}
