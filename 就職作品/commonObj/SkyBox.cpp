#include "SkyBox.h"
#include"../DirectX/Direct3D.h"

SkyBox::SkyBox()
{
	mesh = GetResource.GetXFILE(Sky_M);
	D3DXMatrixTranslation(&mat, 0, 0, 0);
}

SkyBox::~SkyBox()
{
}

void SkyBox::Draw()
{
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ

	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);

	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
}