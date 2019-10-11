#include "SnowFrag.h"

SnowFrag::SnowFrag(D3DXVECTOR3 Pos)
{
	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] = Pos;
	}
	srand(timeGetTime());
	mesh = resourceManager->GetXFILE("commonObj/SnowBall.x");
	for (int i = 0; i < FRAG_NUM; i++)
	{
		D3DXMatrixScaling(&scalMat[i], 0.25f, 0.25f, 0.25f);		//ランダムに少しサイズが変化する　ようにする
		fragVec[i].x = (rand() % 3) / 10.0f;						//ランダムに飛ぶ方向が変わる
		fragVec[i].y = (rand() % 15) / 10.0f;
		fragVec[i].z = (rand() % 3) / 10.0f;
	}
	deleteTime = 3 * 60;
}

SnowFrag::~SnowFrag()
{
}

void SnowFrag::Draw()
{
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			//ライティング
	for (int i = 0; i < FRAG_NUM; i++)
	{
		lpD3DDevice->SetTransform(D3DTS_WORLD, &mat[i]);
		DrawMesh(&mesh);
	}
	
}

bool SnowFrag::Update()
{
	
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
		mat[i] = scalMat[i] * transMat[i];			//行列合成
	}

	deleteTime--;
	if (deleteTime < 0)		//DeleteTimeが0になったら消す
	{
		return false;
	}
	return true;
}

void SnowFrag::SetPos(D3DXVECTOR3 Pos)
{
	for (int i = 0; i < FRAG_NUM; i++)
	{
		fragPos[i] = Pos;
	}
}
