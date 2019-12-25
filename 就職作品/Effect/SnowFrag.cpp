#include "SnowFrag.h"

SnowFrag::SnowFrag(const D3DXVECTOR3 &Pos)
{
	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] = Pos;
	}
	srand(timeGetTime());
	
	fragTex = resourceManager->GetTexture("SnowFrag.png", 1024, 1024, NULL);

	for (int i = 0; i < FRAG_NUM; i++)
	{
		D3DXMatrixScaling(&scalMat[i], 0.25f, 0.25f, 0.25f);		//�����_���ɏ����T�C�Y���ω�����@�悤�ɂ���
		fragVec[i].x = (rand() % 3) / 10.0f;						//�����_���ɔ�ԕ������ς��
		fragVec[i].y = (rand() % 15) / 10.0f;
		fragVec[i].z = (rand() % 3) / 10.0f;
	}
	//deleteTime = 3 * 60;
	//----------------------------------------------------------------------
	//������
	//----------------------------------------------------------------------
	smokeTex = resourceManager->GetTexture("FallingSnow.png", 250, 250, NULL);
	D3DXMatrixTranslation(&smokeMat, Pos.x, Pos.y, Pos.z);
}

SnowFrag::~SnowFrag()
{
}

void SnowFrag::Draw()
{
	lpD3DDevice->SetFVF(FVF_VERTEX);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//���C�e�B���O
	//lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//�t�H�O��
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�J�����O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//���Z�����I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Z�o�b�t�@�������݃I�t

	lpD3DDevice->SetTexture(0, fragTex);

	for (int i = 0; i < FRAG_NUM; i++)
	{
		lpD3DDevice->SetTransform(D3DTS_WORLD, &mat[i]);
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, fragV, sizeof(VERTEX));
	}

	lpD3DDevice->SetTexture(0, smokeTex);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &smokeBillBoardMat);

	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smokeV, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//���C�e�B���O
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//���Z�����I�t
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�J�����O�I��
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Z�o�b�t�@�������݃I��
}

bool SnowFrag::Update()
{
	smokeV[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	smokeV[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	smokeV[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	smokeV[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	smokeV[0].Pos = D3DXVECTOR3(-1.5f * smokeScaling, 1.5f * smokeScaling, 0.0f);
	smokeV[1].Pos = D3DXVECTOR3(1.5f * smokeScaling, 1.5f * smokeScaling, 0.0f);
	smokeV[2].Pos = D3DXVECTOR3(1.5f * smokeScaling, -1.5f * smokeScaling, 0.0f);
	smokeV[3].Pos = D3DXVECTOR3(-1.5f * smokeScaling, -1.5f * smokeScaling, 0.0f);

	fragV[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	fragV[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	fragV[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	fragV[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	fragV[0].Pos = D3DXVECTOR3(-0.3f, 0.3f, 0.0f);
	fragV[1].Pos = D3DXVECTOR3(0.3f, 0.3f, 0.0f);
	fragV[2].Pos = D3DXVECTOR3(0.3f, -0.3f, 0.0f);
	fragV[3].Pos = D3DXVECTOR3(-0.3f, -0.3f, 0.0f);

	smokeScaling += 0.03f;
	alpha--;
	//�����Ȃ��Ȃ�����폜
	if (alpha < 0)
	{
		return false;
	}

	smokeV[0].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	smokeV[1].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	smokeV[2].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	smokeV[3].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	fragV[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fragV[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fragV[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	fragV[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	float Gravity = 0.1f;		//�����͈Ⴄ�O���r�e�B

	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragVec[i].y -= Gravity;
	}

	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] += fragVec[i];
		D3DXMatrixTranslation(&transMat[i], fragPos[i].x, fragPos[i].y, fragPos[i].z);
	}

	for (int i = 0; i < FRAG_NUM; i++)
	{
		mat[i] = fragBillBoardMat * transMat[i];			//�s�񍇐�
	}

	//deleteTime--;
	//if (deleteTime < 0)		//DeleteTime��0�ɂȂ��������
	//{
	//	return false;
	//}
	return true;
}

void SnowFrag::SetPos(D3DXVECTOR3 Pos)
{
	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] = Pos;
	}
}

void SnowFrag::SetBillBoardMat(D3DXMATRIX BillBoardMat)
{
	smokeBillBoardMat = BillBoardMat * smokeMat;
	fragBillBoardMat = BillBoardMat;
}