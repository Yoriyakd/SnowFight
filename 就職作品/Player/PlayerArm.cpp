#include "PlayerArm.h"

PlayerArm::PlayerArm()
{
	armMeshR = resourceManager->GetXFILE("ArmR.x");
	D3DXMatrixTranslation(&armOffsetMatR, 1.0f, 4.0f, 0.0f);		//プレイヤーの原点からの距離		//カメラを親にする

	armAng = 0.0f;
	D3DXMatrixRotationX(&armRotMatXR, D3DXToRadian(-armAng));
}

PlayerArm::~PlayerArm()
{
}

void PlayerArm::Draw(void)
{
	//--------------------------------------------------------------
	//腕表示
	//--------------------------------------------------------------
	lpD3DDevice->SetTransform(D3DTS_WORLD, &armMatR);
	DrawMesh(&armMeshR);
}

void PlayerArm::Update(void)
{
	armMatR = armRotMatXR * armOffsetMatR/* * mat*/;		//カメラの上下に合わせて動かす	matにプレイヤーのY軸回転が入っている	//カメラの回転もらう
}
