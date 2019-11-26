#include "StageHedge.h"
//=====================================
//public���\�b�h
//=====================================


StageHedge::StageHedge(D3DXVECTOR3 * Pos)
{
	//���ォ�玞�v���
	fence[0].Pos = D3DXVECTOR3(0.0f, 4.0f, -8.0f);
	fence[1].Pos = D3DXVECTOR3(0.0f, 4.0f, 8.0f);
	fence[2].Pos = D3DXVECTOR3(0.0f, -4.0f, 8.0f);
	fence[3].Pos = D3DXVECTOR3(0.0f, -4.0f, -8.0f);

	fence[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	fence[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	fence[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	fence[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	fence[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fence[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fence[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fence[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	tex = resourceManager->GetTexture("Hedge.png", 512, 512, NULL);
	D3DXMatrixTranslation(&mat, Pos->x, Pos->y, Pos->z);
}

StageHedge::StageHedge(D3DXVECTOR3 * Pos, float Ang)
{
	//���ォ�玞�v���
	fence[0].Pos = D3DXVECTOR3(0.0f, 4.0f, -8.0f);
	fence[1].Pos = D3DXVECTOR3(0.0f, 4.0f, 8.0f);
	fence[2].Pos = D3DXVECTOR3(0.0f, -4.0f, 8.0f);
	fence[3].Pos = D3DXVECTOR3(0.0f, -4.0f, -8.0f);

	fence[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	fence[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	fence[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	fence[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	fence[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fence[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fence[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fence[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	tex = resourceManager->GetTexture("Hedge.png", 512, 512, NULL);

	D3DXMATRIX TmpTransMat, TmpRotMatY;

	D3DXMatrixRotationY(&TmpRotMatY, D3DXToRadian(Ang));
	D3DXMatrixTranslation(&TmpTransMat, Pos->x, Pos->y, Pos->z);

	mat = TmpRotMatY * TmpTransMat;
}



StageHedge::~StageHedge()
{
}

void StageHedge::Draw(void)
{
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�J�����O
	lpD3DDevice->SetTexture(0, tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, fence, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//���C�e�B���O
}
