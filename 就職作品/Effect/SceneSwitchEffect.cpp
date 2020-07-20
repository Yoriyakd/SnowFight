#include "SceneSwitchEffect.h"
#include"../DirectX/Sprite.h"

SceneSwitchEffect::SceneSwitchEffect() : switchFlag(false), effectAlpha(0)
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
	Sprite::GetInstance().GetSprite()->SetTransform(&effectMat);
	Sprite::GetInstance().GetSprite()->Draw(effectTex, &RcSwitchEffect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(effectAlpha, 255, 255, 255));
}

void SceneSwitchEffect::Update()
{
	if(nowState == FADE_IN)ToBrightness();
	if(nowState == FADE_OUT)ToDarkness();
}

void SceneSwitchEffect::PlayFadeIn(void)
{
	nowState = FADE_IN;
}

void SceneSwitchEffect::PlayFadeOut(void)
{
	nowState = FADE_OUT;
}

SwitchEffectState SceneSwitchEffect::GetFadeState()
{
	return nowState;
}


void SceneSwitchEffect::ToDarkness(void)
{
	if (switchFlag == true)		//�J�ڃt���O�������Ă���Ȃ�؂�ւ���
	{
		switchFlag = false;		//�t���O������
		nowState = STOP;
		return;
	}

	effectAlpha += 20;
	if (effectAlpha > 255)		//�A���t�@�l��255�܂�
	{
		effectAlpha = 255;
		switchFlag = true;
	}
}

void SceneSwitchEffect::ToBrightness(void)
{
	if (switchFlag == true)			//�J�ڃt���O�������Ă���Ȃ�؂�ւ���
	{
		switchFlag = false;		//�t���O������
		nowState = STOP;
		return;
	}
	

	effectAlpha -= 20;

	if (effectAlpha < 0)
	{
		effectAlpha = 0;
		switchFlag = true;
	}
}
