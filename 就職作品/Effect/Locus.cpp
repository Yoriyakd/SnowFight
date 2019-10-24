#include "Locus.h"

SnowLocus::SnowLocus(D3DXMATRIX Mat)
{
	mat = Mat;
	vertex[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);


	tex = resourceManager->GetTexture("Effect/FallingSnow.png", 250, 250, NULL);
}

SnowLocus::~SnowLocus()
{
}

void SnowLocus::SetMat(D3DXMATRIX SnowBallMat)
{
	mat = SnowBallMat;
}

void SnowLocus::Draw()
{
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//加算合成オン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Zバッファ書き込みオフ

	lpD3DDevice->SetTexture(0, tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	//lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン
}

bool SnowLocus::Update()
{
	vertex[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	vertex[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	//D3DXVec3TransformCoord(&vertex[0].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &mat);
	//D3DXVec3TransformCoord(&vertex[1].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &mat);
	//D3DXVec3TransformCoord(&vertex[2].Pos, &D3DXVECTOR3(1.0f, 3.0f, 0.0f), &mat);
	//D3DXVec3TransformCoord(&vertex[3].Pos, &D3DXVECTOR3(-1.0f, 3.0f, 0.0f), &mat);

	vertex[0].Pos = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	vertex[1].Pos = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertex[2].Pos = D3DXVECTOR3(1.0f, 3.0f, 0.0f);
	vertex[3].Pos = D3DXVECTOR3(-1.0f, 3.0f, 0.0f);

	mat * billBoardMat;			//できない

	//段々と薄くしていく
	alpha -= 5;

	//見えなくなったら削除
	if (alpha < 0)
	{
		return false;
	}

	vertex[0].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	return true;
}

void SnowLocus::SetBillBoardMat(D3DXMATRIX BillBoardMat)
{
	billBoardMat = BillBoardMat;
}
