#include "SceneSwitchEffect.h"

SceneSwitchEffect::SceneSwitchEffect() : switchFlag(false)
{
	effectTex = GetResource.GetTexture(SceneSwitch_Tex);
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
	if (switchFlag == true)		//遷移フラグが立っているなら切り替える
	{
		switchFlag = false;		//フラグを下す
		return true;
	}

	effectAlpha += 20;
	if (effectAlpha > 255)		//アルファ値が255まで
	{
		effectAlpha = 255;
		switchFlag = true;
		
	}

	
	return false;
}

bool SceneSwitchEffect::ToBrightness(void)
{
	if (switchFlag == true)			//遷移フラグが立っているなら切り替える
	{
		switchFlag = false;		//フラグを下す
		return true;
	}
	

	effectAlpha -= 20;

	if (effectAlpha < 0)
	{
		effectAlpha = 0;
		switchFlag = true;
	}

	return false;
}
