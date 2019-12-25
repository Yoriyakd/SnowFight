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
		D3DXMatrixScaling(&scalMat[i], 0.25f, 0.25f, 0.25f);		//ランダムに少しサイズが変化する　ようにする
		fragVec[i].x = (rand() % 3) / 10.0f;						//ランダムに飛ぶ方向が変わる
		fragVec[i].y = (rand() % 15) / 10.0f;
		fragVec[i].z = (rand() % 3) / 10.0f;
	}
	//deleteTime = 3 * 60;
	//----------------------------------------------------------------------
	//煙処理
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
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	//lpD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);	//フォグ☆
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//加算合成オン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Zバッファ書き込みオフ

	lpD3DDevice->SetTexture(0, fragTex);

	for (int i = 0; i < FRAG_NUM; i++)
	{
		lpD3DDevice->SetTransform(D3DTS_WORLD, &mat[i]);
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, fragV, sizeof(VERTEX));
	}

	lpD3DDevice->SetTexture(0, smokeTex);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &smokeBillBoardMat);

	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smokeV, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン
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
	//見えなくなったら削除
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

	float Gravity = 0.1f;		//ここは違うグラビティ

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
		mat[i] = fragBillBoardMat * transMat[i];			//行列合成
	}

	//deleteTime--;
	//if (deleteTime < 0)		//DeleteTimeが0になったら消す
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