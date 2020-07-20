#pragma once
#include"../SingletonBase.h"
#include"Direct3D.h"

class Font : public SingletonBase<Font>
{
	friend SingletonBase<Font>;
public:
	const LPD3DXFONT& GetFont(void);

private:
	Font(void);
	~Font();

	void CreateFontObject(void);

	// スプライト
	LPD3DXFONT lpFont;
};
