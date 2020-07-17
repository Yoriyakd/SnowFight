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
	camLookAt = *TreePos;		//注視点を設定
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
	D3DXMATRIX mView, mProj;		//視点行列,投影行列
	
	//視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&camPos,	// カメラの位置	
		&camLookAt,	// カメラの視点
		&D3DXVECTOR3(0, 1, 0)
	);


	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 2000.0f);

	//行列設定
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_VIEW, &mView);
	Direct3D::GetInstance().GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &mProj);
}
