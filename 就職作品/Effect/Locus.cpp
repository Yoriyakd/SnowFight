#include "Locus.h"

SnowLocus::SnowLocus(D3DXMATRIX Mat)
{
	D3DXMatrixTranslation(&mat, Mat._41, Mat._42, Mat._43);

	vertex[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);


	tex = resourceManager->GetTexture("FallingSnow.png", 250, 250, NULL);
}

SnowLocus::~SnowLocus()
{
}

void SnowLocus::Draw()
{
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//���C�e�B���O
	//lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//�t�H�O��
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�J�����O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//���Z�����I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Z�o�b�t�@�������݃I�t

	lpD3DDevice->SetTexture(0, tex);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &billBoardMat);

	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���Z�����I�t
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Z�o�b�t�@�������݃I��
}

bool SnowLocus::Update()
{
	vertex[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	vertex[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	vertex[0].Pos = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertex[1].Pos = D3DXVECTOR3(0.5f, 0.5f, 0.0f);
	vertex[2].Pos = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertex[3].Pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);


	//�i�X�Ɣ������Ă���
	alpha -= 5;

	//�����Ȃ��Ȃ�����폜
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
	billBoardMat = BillBoardMat * mat;
}
