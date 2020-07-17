#include "ResultCam.h"
#include"../DirectX/Direct3D.h"

ResultCam::ResultCam()
{
	camAng = 0.0f;
}

ResultCam::~ResultCam()
{
}

void ResultCam::Update(const D3DXVECTOR3 * TreePos)
{
	camLookAt = *TreePos;		//�����_��ݒ�
	camLookAt.y = CAM_HIGHT;

	camAng += 0.5f;
	if (camAng > 360)
	{
		camAng = 0;
	}

	camPos.x = (float)(treeDistance * cos(D3DXToRadian(camAng)) + TreePos->x);
	camPos.y = CAM_HIGHT;
	camPos.z = (float)(treeDistance * sin(D3DXToRadian(camAng)) + TreePos->z);
}

void ResultCam::SetCamera(void)
{
	D3DXMATRIX mView, mProj;		//���_�s��,���e�s��
	
	//���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&camPos,	// �J�����̈ʒu	
		&camLookAt,	// �J�����̎��_
		&D3DXVECTOR3(0, 1, 0)
	);


	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 2000.0f);

	//�s��ݒ�
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_VIEW, &mView);
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mProj);
}
