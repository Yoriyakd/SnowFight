#include "PlayerArm.h"

PlayerArm::PlayerArm()
{
	armMeshR = resourceManager->GetXFILE("ArmR.x");
	D3DXMatrixTranslation(&armOffsetMatR, 1.0f, 4.0f, 0.0f);		//�v���C���[�̌��_����̋���		//�J������e�ɂ���

	armAng = 0.0f;
	D3DXMatrixRotationX(&armRotMatXR, D3DXToRadian(-armAng));
}

PlayerArm::~PlayerArm()
{
}

void PlayerArm::Draw(void)
{
	//--------------------------------------------------------------
	//�r�\��
	//--------------------------------------------------------------
	lpD3DDevice->SetTransform(D3DTS_WORLD, &armMatR);
	DrawMesh(&armMeshR);
}

void PlayerArm::Update(void)
{
	armMatR = armRotMatXR * armOffsetMatR/* * mat*/;		//�J�����̏㉺�ɍ��킹�ē�����	mat�Ƀv���C���[��Y����]�������Ă���	//�J�����̉�]���炤
}
