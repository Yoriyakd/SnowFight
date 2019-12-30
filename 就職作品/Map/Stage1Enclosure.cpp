#include "Stage1Enclosure.h"

Stage1Enclosure::Stage1Enclosure(StageBorder * StageBorder)
{
	p_StageBorder = StageBorder;

	vEnclosure[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	vEnclosure[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	vEnclosure[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	vEnclosure[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	vEnclosure[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vEnclosure[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vEnclosure[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vEnclosure[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	hedgeTex = GetResource.GetTexture(Hedge_Tex);
	brickTex = GetResource.GetTexture(Brick_Tex);
	poleTex = GetResource.GetTexture(Pole_Tex);
}

Stage1Enclosure::~Stage1Enclosure()
{
}

void Stage1Enclosure::Draw()
{
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング

	
	static const int FenceCnt = 18;		//ステージサイズに合わせた数

	//左上から時計回り
	vEnclosure[0].Pos = D3DXVECTOR3(-8.0f, 4.0f, -0.0f);
	vEnclosure[1].Pos = D3DXVECTOR3(8.0f, 4.0f, 0.0f);
	vEnclosure[2].Pos = D3DXVECTOR3(8.0f, -4.0f, 0.0f);
	vEnclosure[3].Pos = D3DXVECTOR3(-8.0f, -4.0f, -0.0f);

	for (int i = 0; i < FenceCnt; i++)		//stageTop
	{
		D3DXMATRIX TmpMat;

		D3DXMatrixTranslation(&TmpMat, (16.0f * (i - 1)) + 8, 4.0f, (p_StageBorder->Top + 2));
		lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
		lpD3DDevice->SetTexture(0, hedgeTex);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vEnclosure, sizeof(VERTEX));
		
	}

	for (int i = 0; i < FenceCnt; i++)		//stageBottom
	{
		D3DXMATRIX TmpMat;

		D3DXMatrixTranslation(&TmpMat, (16.0f * (i - 1)) + 8, 4.0f, (p_StageBorder->Bottom - 2));		//1枚のサイズ(16) * 枚数(i - 1)いい感じに隅がクロスするようにしている
		lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
		lpD3DDevice->SetTexture(0, hedgeTex);

		if (i >= 7 && i <=10)		//セットするテクスチャを変える		7～10枚目
		{
			lpD3DDevice->SetTexture(0, brickTex);
		}

		if (i >= 8 && i <= 9)		//セットするテクスチャを変える		8,9枚目
		{
			lpD3DDevice->SetTexture(0, poleTex);
		}

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vEnclosure, sizeof(VERTEX));
	}

	//左上から時計回り
	vEnclosure[0].Pos = D3DXVECTOR3(0.0f, 4.0f, -8.0f);
	vEnclosure[1].Pos = D3DXVECTOR3(0.0f, 4.0f, 8.0f);
	vEnclosure[2].Pos = D3DXVECTOR3(0.0f, -4.0f, 8.0f);
	vEnclosure[3].Pos = D3DXVECTOR3(0.0f, -4.0f, -8.0f);

	for (int i = 0; i < FenceCnt; i++)		//stageLeft
	{
		D3DXMATRIX TmpMat;

		D3DXMatrixTranslation(&TmpMat, p_StageBorder->Left - 2, 4.0f, (16.0f * (i - 1)) + 8);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
		lpD3DDevice->SetTexture(0, hedgeTex);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vEnclosure, sizeof(VERTEX));
	}

	for (int i = 0; i < FenceCnt; i++)		//stageRight
	{
		D3DXMATRIX TmpMat;

		D3DXMatrixTranslation(&TmpMat, p_StageBorder->Right + 2, 4.0f, (16.0f * (i - 1)) + 8);
		lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);
		lpD3DDevice->SetTexture(0, hedgeTex);

		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vEnclosure, sizeof(VERTEX));
	}

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリング
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
}
