#include "Locus.h"

SnowLocus::SnowLocus(D3DXMATRIX Mat)
{
	mat = Mat;
	vertex[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);


	tex = resourceManager->GetTexture("Effect/Locus.png", 64, 64, NULL);
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
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//�t�H�O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�J�����O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//���Z�����I��

	lpD3DDevice->SetTexture(0, tex);
	D3DXMATRIX IdenMat;
	D3DXMatrixIdentity(&IdenMat);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);

	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertex, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���Z�����I�t
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�I��
}

bool SnowLocus::Update()
{
	vertex[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	vertex[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	D3DXVec3TransformCoord(&vertex[0].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &mat);
	D3DXVec3TransformCoord(&vertex[1].Pos, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &mat);
	D3DXVec3TransformCoord(&vertex[2].Pos, &D3DXVECTOR3(1.0f, 0.0f, 3.0f), &mat);
	D3DXVec3TransformCoord(&vertex[3].Pos, &D3DXVECTOR3(-1.0f, 0.0f, 3.0f), &mat);

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
}
