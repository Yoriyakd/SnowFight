#include "SnowFrag.h"

SnowFrag::SnowFrag(D3DXVECTOR3 Pos)
{
	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] = Pos;
	}
	srand(timeGetTime());
	mesh = resourceManager->GetXFILE("SnowBall.x");
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
	tex = resourceManager->GetTexture("FallingSnow.png", 250, 250, NULL);
	D3DXMatrixTranslation(&smokeMat, Pos.x, Pos.y, Pos.z);
}

SnowFrag::~SnowFrag()
{
}

void SnowFrag::Draw()
{
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//���C�e�B���O
	for (int i = 0; i < FRAG_NUM; i++)
	{
		lpD3DDevice->SetTransform(D3DTS_WORLD, &mat[i]);
		DrawMesh(&mesh);
	}

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

bool SnowFrag::Update()
{
	vertex[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	vertex[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	vertex[0].Pos = D3DXVECTOR3(-1.5f * smokeScaling, 1.5f * smokeScaling, 0.0f);
	vertex[1].Pos = D3DXVECTOR3(1.5f * smokeScaling, 1.5f * smokeScaling, 0.0f);
	vertex[2].Pos = D3DXVECTOR3(1.5f * smokeScaling, -1.5f * smokeScaling, 0.0f);
	vertex[3].Pos = D3DXVECTOR3(-1.5f * smokeScaling, -1.5f * smokeScaling, 0.0f);

	smokeScaling += 0.03f;
	alpha--;
	//�����Ȃ��Ȃ�����폜
	if (alpha < 0)
	{
		return false;
	}

	vertex[0].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	vertex[1].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	vertex[2].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);
	vertex[3].Color = D3DCOLOR_ARGB(alpha, 255, 255, 255);

	float Gravity = 0.1f;

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
		mat[i] = scalMat[i] * transMat[i];			//�s�񍇐�
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
	billBoardMat = BillBoardMat * smokeMat;
}