#include "StageFence.h"

StageFence::StageFence(void)
{
	mesh = resourceManager->GetXFILE("Map/Fence.x");
}

StageFence::~StageFence()
{
}

//=====================================
//publicƒƒ\ƒbƒh
//=====================================


void StageFence::SetMat(D3DXVECTOR3 Pos)
{
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
}

void StageFence::SetMat(D3DXVECTOR3 Pos, float Ang)
{
	D3DXMatrixTranslation(&mat, Pos.x, Pos.y, Pos.z);
	D3DXMATRIX TmpRotMat;
	D3DXMatrixRotationY(&TmpRotMat, D3DXToRadian(Ang));
	mat = TmpRotMat * mat;
}

void StageFence::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD ,&mat);
	DrawMesh(&mesh);
}
