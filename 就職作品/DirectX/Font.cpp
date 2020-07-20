#include"Font.h"

void Font::CreateFontObject(void)
{
	if (lpFont != nullptr)
	{
		return;
	}

	D3DXCreateFont(Direct3D::GetInstance().GetD3DDevice(), 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "‚l‚r ƒSƒVƒbƒN", &lpFont);

	lpFont->OnResetDevice();
}

const LPD3DXFONT& Font::GetFont(void)
{
	return lpFont;
}


Font::Font(void)
{
	CreateFontObject();
}

Font::~Font()
{
	lpFont->Release();
}