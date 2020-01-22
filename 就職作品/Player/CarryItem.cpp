#include "CarryItem.h"

CarryItem::CarryItem(const D3DXMATRIX *ArmRMat) : armRMat_p(ArmRMat)
{
	RedBallMesh = GetResource.GetXFILE(Decoration_RedBall_M);
	BlueBallMesh = GetResource.GetXFILE(Decoration_BlueBall_M);
	YellowBallMesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	SnowBallMesh = GetResource.GetXFILE(SnowBall_M);

	//--------------------------------------------------------------
	//保持している雪玉、デコレーション
	//--------------------------------------------------------------
	D3DXMatrixTranslation(&itemOffsetMat, 0.3f, 0.4f, 1.0f);		//手からいくら離すか
	nowCarryItemMesh = nullptr;

	D3DXMatrixScaling(&ScalingMat, 0.3f, 0.3f, 0.3f);
}

CarryItem::~CarryItem()
{
}

void CarryItem::Draw()
{
	//--------------------------------------------------------------
	//保持している雪玉、デコレーション表示
	//--------------------------------------------------------------
	if (*id != NUM_ITEM_Dummy)
	{
		if (*id != SNOW_BALL)
		{
			D3DXMATRIX TmpMat;
			TmpMat = ScalingMat * itemMat;
			lpD3DDevice->SetTransform(D3DTS_WORLD, &TmpMat);				//雪玉ではない場合小さくする
			lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}
		else
		{
			lpD3DDevice->SetTransform(D3DTS_WORLD, &itemMat);
		}
		
		DrawMesh(nowCarryItemMesh);
	}
	lpD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

void CarryItem::Updata()
{
	itemMat = itemOffsetMat * *armRMat_p;

	switch (*id)
	{
	case RED_BALL:
		nowCarryItemMesh = &RedBallMesh;
		break;
	case BLUE_BALL:
		nowCarryItemMesh = &BlueBallMesh;
		break;
	case YELLOW_BALL:
		nowCarryItemMesh = &YellowBallMesh;
		break;
	case SNOW_BALL:
		nowCarryItemMesh = &SnowBallMesh;
		break;
	case NUM_ITEM_Dummy:
		nowCarryItemMesh = nullptr;
		break;
	}
}

void CarryItem::SetNowCarryItemPointer(const CarryObjectID * _ID)
{
	id = _ID;
}


