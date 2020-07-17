#include "SnowFrag.h"
#include"../DirectX/Direct3D.h"

SnowFrag::SnowFrag(const D3DXVECTOR3 &Pos) : smokeScaling(0)/*, secondSmokeScaling(0)*/, alpha(128)/*, secondAlpha(128)*/
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
	D3DXMatrixTranslation(&smokeMat, Pos.x, Pos.y, Pos.z);
	//D3DXMatrixTranslation(&secondSmokeMat, Pos.x, Pos.y, Pos.z);
}

SnowFrag::~SnowFrag()
{
}

void SnowFrag::Draw()
{
	Direct3D::GetInstance().GetD3DDevice()->SetFVF(FVF_VERTEX);
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);		//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		//加算合成オン
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//Zバッファ書き込みオフ

	Direct3D::GetInstance().GetD3DDevice()->SetTexture(0, fragTex);

	for (int i = 0; i < FRAG_NUM; i++)
	{
		Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &fragMat[i]);
		Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, fragV, sizeof(VERTEX));
	}

	Direct3D::GetInstance().GetD3DDevice()->SetTexture(0, smokeTex);

	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &smokeBillBoardMat);

	Direct3D::GetInstance().GetD3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, smokeV, sizeof(VERTEX));

	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);		//ライティング
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		//加算合成オフ
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//カリングオン
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//Zバッファ書き込みオン
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

	if (smokeScaling <= 2.5f)
	{
		smokeScaling += 0.8f;
	}
	else
	{
		smokeScaling += 0.05f;
	}


	alpha -= 3;

	if (alpha < 0)
	{
		alpha = 0;
	}

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
		fragMat[i] = fragBillBoardMat * transMat[i];			//行列合成
	}

	return true;
}

void SnowFrag::SetBillBoardMat(D3DXMATRIX BillBoardMat)
{
	smokeBillBoardMat = BillBoardMat * smokeMat;
	fragBillBoardMat = BillBoardMat;
}