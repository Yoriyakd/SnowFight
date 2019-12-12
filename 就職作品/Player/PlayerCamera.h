#pragma once
#include<d3dx9.h>
#include"../main.h"
//----------------------------------------
//�v���C���[�̃J�����N���X
//�ړ��⎋�_�����S��
//----------------------------------------
class PlayerCamera {
public:
	PlayerCamera();
	~PlayerCamera();
	void Update(StageBorder & StageBorder);
	void SetCamera(void);
	//--------------------------------------------------
	//Getter
	//--------------------------------------------------
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetmView(void);
	D3DXVECTOR3 GetmoveVec(void);					//�v���C���[�̈ړ��x�N�g����Ԃ�
	D3DXVECTOR3 GetPos(void);
	//--------------------------------------------------
	//Setter
	//--------------------------------------------------
	void PushPos(D3DXVECTOR3 *PushVec);				//�����o���x�N�g����^����(�����蔻��̂Ƃ���Ŏg��)
	void SetPos(D3DXVECTOR3 *SetPos);
	void SetMakeSnowBaallFlag(bool Flag);			//

private:
	//--------------------------------------------------
	//�}�E�X�ŃJ�����𓮂����p�̕ϐ��Q
	//--------------------------------------------------
	POINT basePt;
	//--------------------------------------------------
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	//-------------------------------------------------
	//�ݒ�p�̕ϐ�(�����̒l��ύX����)
	//-------------------------------------------------
	const float moveSpeed = 0.5f;
	const float camHight = 5.0f;		//�J������y0����̍���
	//-------------------------------------------------

	D3DXMATRIX billBoardMat;		//������r���{�[�h�̍s������Ă���
	D3DXVECTOR3 moveVec;		//�ړ��x�N�g����ۑ����Ă������莞�ɓn��
	D3DXMATRIX mView, mProj;		//���_�s��,���e�s��

	bool MakeSnowBallFlag;		//true�̎���ʍ쐬�̎p���ɂȂ�
	float mouseSensitivityX = 1.0f, mouseSensitivityY = 1.0f;			//�}�E�X���x�����p�ϐ�
	//--------------------------------------------------
	//���\�b�h
	//--------------------------------------------------
	void Move(StageBorder & StageBorder);
	void MakeSnowBallPose(void);

};
