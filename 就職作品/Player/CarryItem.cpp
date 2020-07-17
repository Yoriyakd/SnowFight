#include "CarryItem.h"
#include"../DirectX/Direct3D.h"

CarryItem::CarryItem(const D3DXMATRIX *ArmRMat) : armRMat_p(ArmRMat)
{
	RedBallMesh = GetResource.GetXFILE(Decoration_RedBall_M);
	BlueBallMesh = GetResource.GetXFILE(Decoration_BlueBall_M);
	YellowBallMesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	SnowBallMesh = GetResource.GetXFILE(SnowBall_M);

	//--------------------------------------------------------------
	//�ێ����Ă����ʁA�f�R���[�V����
	//--------------------------------------------------------------
	D3DXMatrixTranslation(&itemOffsetMat, 0.3f, 0.3f, 1.0f);		//�肩�炢���痣����
	nowCarryItemMesh = nullptr;

	D3DXMatrixScaling(&ScalingMat, 0.4f, 0.4f, 0.4f);
}

CarryItem::~CarryItem()
{
}

void CarryItem::Draw()
{
	//--------------------------------------------------------------
	//�ێ����Ă����ʁA�f�R���[�V�����\��
	//--------------------------------------------------------------
	if (displayFlag == true)		//�\���t���O��true�Ȃ�\��
	{
		if (*id != SNOW_BALL)
		{
			D3DXMATRIX TmpMat;
			TmpMat = ScalingMat * itemMat;
			Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &TmpMat);				//��ʂł͂Ȃ��ꍇ����������
			Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);		//�@���̍Čv�Z
		}
		else
		{
			Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_WORLD, &itemMat);
		}
		
		DrawMesh(nowCarryItemMesh);
	}
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
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
		break;
	}
}

void CarryItem::SetNowCarryItemPointer(const CarryObjectID * _ID)
{
	id = _ID;
}

void CarryItem::SetDisplayFlag(bool _Flag)
{
	displayFlag = _Flag;
}


