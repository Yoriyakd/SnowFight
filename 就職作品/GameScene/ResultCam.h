#pragma once
#include"../main.h"

//--------------------------------------------
//���U���g�\�����c���[�������邽�߂̃J�����ł�
//--------------------------------------------
class ResultCam {
public:
	ResultCam();
	~ResultCam();
	void Update(const D3DXVECTOR3 * TreePos);
	void SetCamera(void);
private:
	const float camHight = 45.0f, treeDistance = 100.0f;
	D3DXVECTOR3 camPos, camLookAt;
	float camAng;		//�J�����̎���^���̊p�x
};