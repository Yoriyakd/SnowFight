#include "SceneSwitchEffect.h"

SceneSwitchEffect::SceneSwitchEffect()
{
	effectTex = GetResource.GetTexture("SceneSwitchEffect.png", 32, 32, NULL);
	D3DXMatrixTranslation(&effectMat, 0, 0, 0);
	effectAlpha = 0;
}

SceneSwitchEffect::~SceneSwitchEffect()
{
}

void SceneSwitchEffect::Draw()
{
	RECT RcSwitchEffect = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&effectMat);
	lpSprite->Draw(effectTex, &RcSwitchEffect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(effectAlpha, 255, 255, 255));
}


bool SceneSwitchEffect::ToDarkness(void)
{
	effectAlpha += 20;
	if (effectAlpha > 255)		//アルファ値が255まで
	{
		effectAlpha = 255;

		return true;
	}
	return false;
}

bool SceneSwitchEffect::ToBrightness(void)
{
	effectAlpha -= 20;

	if (effectAlpha < 0)
	{
		effectAlpha = 0;

		return true;
	}
	return false;
}
