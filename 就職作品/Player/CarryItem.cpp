#include "CarryItem.h"

CarryItem::CarryItem(const D3DXMATRIX *ArmRMat) : armRMat_p(ArmRMat)
{
	RedBallMesh = GetResource.GetXFILE(Decoration_RedBall_M);
	BlueBallMesh = GetResource.GetXFILE(Decoration_BlueBall_M);
	YellowBallMesh = GetResource.GetXFILE(Decoration_YellowBall_M);

	//--------------------------------------------------------------
	//�ێ����Ă����ʁA�f�R���[�V����
	//--------------------------------------------------------------
	D3DXMatrixTranslation(&itemOffsetMat, 0.3f, 0.4f, 1.0f);		//�肩�炢���痣����
	nowCarryItem = &YellowBallMesh;
}

CarryItem::~CarryItem()
{
}

void CarryItem::Draw()
{
	//--------------------------------------------------------------
	//�ێ����Ă����ʁA�f�R���[�V�����\��
	//--------------------------------------------------------------
	if (nowCarryItem != nullptr)
	{
		lpD3DDevice->SetTransform(D3DTS_WORLD, &itemMat);
		DrawMesh(nowCarryItem);
	}
}

void CarryItem::Updata()
{
	itemMat = itemOffsetMat * *armRMat_p;
	/*if (carryFlag == true)
	{
		switch (carryDecorationID)
		{
		case RED_BALL:
			holdingObj = &RedBallMesh;
			break;
		case BLUE_BALL:
			holdingObj = &BlueBallMesh;
			break;
		case YELLOW_BALL:
			holdingObj = &YellowBallMesh;
			break;
		default:
			holdingObj = nullptr;
			break;
		}
	}


	if (remainingBalls > 0)
	{
		holdingObj = &ballMesh;
	}
	else
	{
		holdingObj = nullptr;
	}*/
}
