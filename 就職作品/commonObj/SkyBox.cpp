#include "SkyBox.h"

SkyBox::SkyBox()
{
	mesh = resourceManager->GetXFILE("Sky.x");
	D3DXMatrixTranslation(&mat, 0, 0, 0);
}

SkyBox::~SkyBox()
{
}

void SkyBox::Draw()
{
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ

	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}