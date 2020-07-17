#include "Ground.h"
#include"../DirectX/Direct3D.h"

Ground::Ground()
{
	ground[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
	ground[1].Pos = D3DXVECTOR3(300.0f, 0.0f, 300.0f);
	ground[2].Pos = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
	ground[3].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ground[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	ground[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	ground[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	ground[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	ground[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	ground[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	ground[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	ground[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	tex = GetResource.GetTexture(Ground_Tex);
}

Ground::~Ground()
{
}

D3DXMATRIX Ground::GetMat()
{
	return mat;
}

void Ground::SetMat(D3DXMATRIX)
{
}

void Ground::Draw()
{
	
	Direct3D::GetInstance().GetD3DDevice()->SetFVF(FVF_VERTEX);
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ

	Direct3D::GetInstance().GetD3DDevice()->SetTexture(0,tex);
	D3DXMatrixTranslation(&mat, -150, 0, 0);
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ground, sizeof(VERTEX));
	D3DXMatrixTranslation(&mat, 150, 0, 0);
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ground, sizeof(VERTEX));
	D3DXMatrixTranslation(&mat, -150, 0, -300);
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ground, sizeof(VERTEX));
	D3DXMatrixTranslation(&mat, 150, 0, -300);
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ground, sizeof(VERTEX));

	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
}