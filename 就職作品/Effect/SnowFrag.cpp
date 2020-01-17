#include "SnowFrag.h"

SnowFrag::SnowFrag(const D3DXVECTOR3 &Pos) : firstSmokeScaling(0)/*, secondSmokeScaling(0)*/, firstAlpha(128)/*, secondAlpha(128)*/
{
	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] = Pos;
	}
	srand(timeGetTime());
	
	fragTex = GetResource.GetTexture(SnowFrag_Tex);

	for (int i = 0; i < FRAG_NUM; i++)
	{
		D3DXMatrixScaling(&scalMat[i], 0.25f, 0.25f, 0.25f);		//ランダムに少しサイズが変化する　ようにする
		fragVec[i].x = (rand() % 3) / 10.0f;						//ランダムに飛ぶ方向が変わる
		fragVec[i].y = (rand() % 15) / 10.0f;
		fragVec[i].z = (rand() % 3) / 10.0f;
	}

	//----------------------------------------------------------------------
	//煙処理
	//----------------------------------------------------------------------
	smokeTex = GetResource.GetTexture(SnowSmoke_Tex);
	D3DXMatrixTranslation(&firstSmokeMat, Pos.x, Pos.y, Pos.z);
	//D3DXMatrixTranslation(&secondSmokeMat, Pos.x, Pos.y, Pos.z);
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
		lpD3DDevice->SetTransform(D3DTS_WORLD, &fragMat[i]);
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, fragV, sizeof(VERTEX));
	}

	lpD3DDevice->SetTexture(0, smokeTex);

	lpD3DDevice->SetTransform(D3DTS_WORLD, &smokeBillBoardMat);

	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, firstSmokeV, sizeof(VERTEX));
	//lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, secondSmokeV, sizeof(VERTEX));

	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン
}

bool SnowFrag::Update()
{
	firstSmokeV[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	firstSmokeV[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	firstSmokeV[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	firstSmokeV[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	firstSmokeV[0].Pos = D3DXVECTOR3(-1.5f * firstSmokeScaling, 1.5f * firstSmokeScaling, 0.0f);
	firstSmokeV[1].Pos = D3DXVECTOR3(1.5f * firstSmokeScaling, 1.5f * firstSmokeScaling, 0.0f);
	firstSmokeV[2].Pos = D3DXVECTOR3(1.5f * firstSmokeScaling, -1.5f * firstSmokeScaling, 0.0f);
	firstSmokeV[3].Pos = D3DXVECTOR3(-1.5f * firstSmokeScaling, -1.5f * firstSmokeScaling, 0.0f);
	
	/*secondSmokeV[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	secondSmokeV[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	secondSmokeV[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	secondSmokeV[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	secondSmokeV[0].Pos = D3DXVECTOR3(-1.5f * secondSmokeScaling, 1.5f * secondSmokeScaling, 0.0f);
	secondSmokeV[1].Pos = D3DXVECTOR3(1.5f * secondSmokeScaling, 1.5f * secondSmokeScaling, 0.0f);
	secondSmokeV[2].Pos = D3DXVECTOR3(1.5f * secondSmokeScaling, -1.5f * secondSmokeScaling, 0.0f);
	secondSmokeV[3].Pos = D3DXVECTOR3(-1.5f * secondSmokeScaling, -1.5f * secondSmokeScaling, 0.0f);*/

	fragV[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	fragV[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	fragV[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	fragV[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	fragV[0].Pos = D3DXVECTOR3(-0.3f, 0.3f, 0.0f);
	fragV[1].Pos = D3DXVECTOR3(0.3f, 0.3f, 0.0f);
	fragV[2].Pos = D3DXVECTOR3(0.3f, -0.3f, 0.0f);
	fragV[3].Pos = D3DXVECTOR3(-0.3f, -0.3f, 0.0f);

	if (firstSmokeScaling <= 2.5f)
	{
		firstSmokeScaling += 0.8f;
	}
	else
	{
		firstSmokeScaling += 0.05f;
	}

	/*if (firstAlpha < 80)
	{
		secondAlpha -= 3;
		if (secondSmokeScaling <= 2.5f)
		{
			secondSmokeScaling += 0.3f;
		}
		else
		{
			secondSmokeScaling += 0.05f;
		}
	}
	else
	{
		
	}*/

	firstAlpha -= 3;

	if (firstAlpha < 0)
	{
		firstAlpha = 0;
	}

	//見えなくなったら削除
	if (firstAlpha < 0)
	{
		return false;
	}

	firstSmokeV[0].Color = D3DCOLOR_ARGB(firstAlpha, 255, 255, 255);
	firstSmokeV[1].Color = D3DCOLOR_ARGB(firstAlpha, 255, 255, 255);
	firstSmokeV[2].Color = D3DCOLOR_ARGB(firstAlpha, 255, 255, 255);
	firstSmokeV[3].Color = D3DCOLOR_ARGB(firstAlpha, 255, 255, 255);
	
	/*secondSmokeV[0].Color = D3DCOLOR_ARGB(secondAlpha, 255, 255, 255);
	secondSmokeV[1].Color = D3DCOLOR_ARGB(secondAlpha, 255, 255, 255);
	secondSmokeV[2].Color = D3DCOLOR_ARGB(secondAlpha, 255, 255, 255);
	secondSmokeV[3].Color = D3DCOLOR_ARGB(secondAlpha, 255, 255, 255);*/

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
		fragMat[i] = fragBillBoardMat * transMat[i];			//行列合成
	}

	return true;
}

void SnowFrag::SetBillBoardMat(D3DXMATRIX BillBoardMat)
{
	smokeBillBoardMat = BillBoardMat * firstSmokeMat;
	fragBillBoardMat = BillBoardMat;
}